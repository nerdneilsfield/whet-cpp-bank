---
qid: cpp-iv-move-007
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, 字节跳动]
rubric:
  - 使用变参模板（variadic template）接受任意数量参数
  - 对参数包使用转发引用 Args&&...
  - 在 new 表达式中通过 std::forward<Args>(args)... 展开参数包
  - 返回类型为 std::unique_ptr<T>
  - 加分：说明为何不用 std::move 而用 std::forward；提到 C++17 guaranteed copy elision 消除返回值拷贝
---

# 写一个 `make_unique<T>(args...)` 的简化实现，正确使用完美转发。

## 参考答案

### 实现

```cpp
#include <memory>
#include <utility>  // std::forward

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```

这四行代码涵盖了完美转发的完整用法，逐行解析如下。

### 逐行解析

**`template<typename T, typename... Args>`**

- `T`：要构造的类型，由调用者显式指定（`make_unique<Foo>(...)`）
- `Args...`：参数包，类型由调用时自动推导，数量任意（0 个到 N 个）

**`std::unique_ptr<T> make_unique(Args&&... args)`**

- `Args&&...` 是**转发引用包**：每个 `Arg_i&&` 都是独立的转发引用
- 调用时按引用折叠推导：左值参数 → `Arg_i = X&`，右值参数 → `Arg_i = X`

**`new T(std::forward<Args>(args)...)`**

- `std::forward<Args>(args)...` 展开参数包：对每个 `args_i` 执行 `std::forward<Args_i>(args_i)`
- 保留每个参数的原始值类别，直接透传给 `T` 的构造函数

### 演示

```cpp
#include <iostream>
#include <string>

struct Foo {
    Foo(int i, std::string s) {
        std::cout << "Foo(" << i << ", " << s << ")\n";
    }
};

int main() {
    auto p1 = make_unique<Foo>(42, std::string("hello"));
    // std::string("hello") 是右值 → 移动构造 string，无拷贝

    std::string s = "world";
    auto p2 = make_unique<Foo>(1, s);
    // s 是左值 → 拷贝构造 string，s 内容不变

    auto p3 = make_unique<int>(100);  // 单参数
    auto p4 = make_unique<std::string>();  // 零参数，默认构造
}
```

### 为何用 `std::forward` 而非 `std::move`

```cpp
// 错误版本：总是移动
template<typename T, typename... Args>
std::unique_ptr<T> bad_make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::move(args)...)); // 危险！
}

std::string s = "hello";
auto p = bad_make_unique<Foo>(1, s);
// s 被 move 了！make_unique 返回后 s 为空字符串
// 调用者传入左值，没想到所有权被夺走
```

`std::forward` 只在传入右值（可以被移走）时才转为右值引用；传入左值时保持左值，安全地拷贝。

### C++14 标准实现的额外细节

标准库实现还需处理数组类型：

```cpp
// 标准做法（C++14 起）
template<typename T, typename... Args>
std::enable_if_t<!std::is_array_v<T>, std::unique_ptr<T>>
make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// 数组版本
template<typename T>
std::enable_if_t<std::is_unbounded_array_v<T>, std::unique_ptr<T>>
make_unique(std::size_t n) {
    return std::unique_ptr<T>(new std::remove_extent_t<T>[n]());
}
```

面试中给出核心单对象版本已足够，提到数组版本会额外加分。
