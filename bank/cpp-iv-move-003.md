---
qid: cpp-iv-move-003
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, Amazon]
rubric:
  - std::move 本质是 static_cast<T&&>，不移动任何数据
  - 真正的移动发生在移动构造/移动赋值函数被调用时
  - 对没有移动构造函数的类型，std::move 会退化到拷贝
  - 对 const 对象 std::move 仍会退化为拷贝（const T&& 无法绑定非 const 移动构造）
  - 加分：说明 std::move 后对象仍合法但处于未指定状态，不应再读其值
---

# `std::move` 的作用是什么？它真的"移动"了数据吗？

## 参考答案

### std::move 的本质

`std::move` **不移动任何数据**。它只是一个类型转换函数，将其参数无条件转换为右值引用：

```cpp
// 标准库的近似实现
template<typename T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}
```

即：`std::move(x)` ≡ `static_cast<T&&>(x)`。

它的唯一作用是**告诉编译器"这个对象可以被移走"**，从而触发移动构造/移动赋值的重载决议。

### 真正的移动在哪里发生？

移动发生在**移动构造函数**或**移动赋值运算符**被调用时：

```cpp
std::string a = "hello world, a long string beyond SSO";
std::string b = std::move(a);  // ← 这里触发 string 的移动构造函数
// string::string(string&& other) noexcept {
//     ptr_ = other.ptr_;   // 接管指针
//     len_ = other.len_;
//     other.ptr_ = nullptr; // 源对象置空
// }
```

`std::move(a)` 只是产生一个 `string&&` 类型的表达式；赋值时匹配到移动构造函数，才真正发生资源转移。

### 两种"退化"情形

**1. 类型没有移动构造函数**

```cpp
struct NoCopy {
    NoCopy(NoCopy&&) = delete;
    NoCopy(const NoCopy&) { /* deep copy */ }
};
NoCopy x;
NoCopy y = std::move(x); // 编译器退化到拷贝构造，仍然发生深拷贝！
```

**2. 对 const 对象调用 std::move**

```cpp
const std::string cs = "immutable";
std::string s = std::move(cs);
// std::move(cs) 产生 const string&&
// 移动构造需要 string&&（非 const），不匹配
// 退化为拷贝构造 string(const string&)，深拷贝！
```

### 移动后对象的状态

`std::move` 后，若移动构造确实发生，源对象处于**"有效但未指定（valid but unspecified）"**状态：

- 可以安全析构（不会崩溃）
- 可以重新赋值
- **不应读取其值**（内容未定义）

```cpp
std::string src = "data";
std::string dst = std::move(src);
// src 仍是合法对象，但 src.empty() 不保证为 true（实践中通常为空）
src = "new data"; // OK：重新赋值后可以正常使用
```

### 总结一句话

> `std::move` 是一张"许可证"，告诉编译器"可以搬走这个对象的资源"；真正的搬运由移动构造/赋值函数执行。
