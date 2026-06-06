---
qid: cpp-iv-move-005
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, 腾讯]
rubric:
  - 引用折叠只在模板/typedef/decltype 中出现，不在普通代码中出现
  - 四条规则：只要有一个 & 结果就是 &；两个 && 才是 &&
  - T& && = T&；T&& & = T&；T& & = T&；T&& && = T&&
  - 结合模板推导解释为何转发引用可同时绑定左值和右值
  - 加分：用 decltype 或 typedef 演示折叠
---

# 引用折叠规则是什么？`T&& &` 和 `T& &&` 分别是什么？

## Explanation

### 为何需要引用折叠

C++ 不允许"引用的引用"（`int& &` 在普通代码中非法），但在**模板实例化、typedef、decltype** 中会出现引用叠加的情况，编译器通过**引用折叠规则**将其化简为合法类型。

### 四条折叠规则

```
T&  &   →  T&      // 左值引用 & 左值引用 = 左值引用
T&  &&  →  T&      // 左值引用 & 右值引用 = 左值引用
T&& &   →  T&      // 右值引用 & 左值引用 = 左值引用
T&& &&  →  T&&     // 右值引用 & 右值引用 = 右值引用
```

**记忆口诀：只要有一个 `&`，结果就是 `&`；只有两个 `&&` 才能保持 `&&`。**

### 代码演示

```cpp
using LR = int&;
using RR = int&&;

LR&  a = ???;  // int& &  → int&
LR&& b = ???;  // int& && → int&
RR&  c = ???;  // int&& & → int&
RR&& d = ???;  // int&&&& → int&&
```

用 `std::add_lvalue_reference` 验证：

```cpp
#include <type_traits>
static_assert(std::is_same_v<int& &&, int&>);   // 通过（通过 typedef 触发折叠）
```

### 转发引用中的折叠机制

这是引用折叠最重要的应用场景：

```cpp
template<typename T>
void f(T&& x);

int a = 1;
f(a);   // 传左值：T 推导为 int&
        // 函数签名变为 f(int& &&) → 折叠为 f(int&)
        // x 的类型是 int&（左值引用）

f(1);   // 传右值：T 推导为 int（无引用）
        // 函数签名为 f(int&&)
        // x 的类型是 int&&（右值引用）
```

引用折叠使得同一个模板函数能正确保存传入参数的值类别（左值还是右值），这正是完美转发的基础。

### 在 `std::forward` 中的应用

```cpp
template<typename T>
T&& forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}
```

- 若 `T = int&`：返回类型 `int& &&` 折叠为 `int&`，传出左值引用。
- 若 `T = int`：返回类型 `int&&`，传出右值引用。

引用折叠是 `std::forward` 能够同时处理左值和右值的底层机制。

### 总结表

| 原始形式 | 折叠结果 |
|---------|---------|
| `T& &`  | `T&`    |
| `T& &&` | `T&`    |
| `T&& &` | `T&`    |
| `T&& &&`| `T&&`   |
