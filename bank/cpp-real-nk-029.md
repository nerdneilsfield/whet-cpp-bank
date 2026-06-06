---
qid: cpp-real-nk-029
type: single
kp: [cpp-move-semantics, cpp-cpp11]
primary_kp: cpp-move-semantics
difficulty: medium
answer_key: B
tags: [interview-real, bytedance]
---

```cpp
template<typename T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}
```

`std::move(x)` 实际做了什么？

A. 移动 x 的资源到新位置，使 x 变为空
B. **仅仅是把 x 的类型强转为右值引用**，本身不会移动任何资源；真正的"移动"是后续移动构造/赋值的事
C. 编译器优化：在 RVO 不能生效时自动调用 move
D. 调用 x 的移动构造函数

---

**解析：**

`std::move` 是 C++ 语义最容易被误解的函数：

1. **move 本身不移动任何东西**，只是把表达式的值类别从左值"扭转"为右值（确切说是 xvalue，将亡值）
2. 实现就是一个 `static_cast<T&&>`，编译期完成，零运行时开销
3. 真正的资源转移发生在**接收 move 后表达式的函数**（如移动构造函数、移动赋值运算符）

例子：
```cpp
std::string s1 = "hello";
std::string s2 = std::move(s1);  // 这里 std::move 只产生右值引用
                                  // 接着 string(string&&) 移动构造函数才真正"偷走" s1 的内部指针
// s1 现在处于 valid but unspecified 状态（不一定为空）
```

注意：
- `std::move(const T x)` 不会真正"移动"，因为 const 对象的移动构造函数等价于拷贝构造
- 把 move 用在返回语句 `return std::move(local)` 通常会**禁止 NRVO**，反而变慢

**来源：** 字节 C++11 面试题 / Effective Modern C++ Item 23