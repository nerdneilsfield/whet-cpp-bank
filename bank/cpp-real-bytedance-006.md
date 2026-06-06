---
qid: cpp-real-bytedance-006
type: single
kp: [cpp-templates, cpp-move-semantics]
primary_kp: cpp-templates
difficulty: hard
answer_key: B
tags: [interview-real, bytedance]
---
```cpp
// std::forward 的简化实现
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, 
                  "forward must not be used to convert an rvalue to an lvalue");
    return static_cast<T&&>(arg);
}
```
关于 `std::forward` 的本质和正确用法，以下说法**正确**的是：

A. forward 总是把参数转为右值，等同 std::move
B. forward 保留入参的**值类别**：若调用方传的是 lvalue，forward 返回 lvalue 引用；若是 rvalue，forward 返回 rvalue 引用。配合通用引用 T&& 实现"完美转发"
C. forward 只能用于函数模板的返回值
D. forward 会增加引用计数

---

**解析：**

选 B。这是 C++11 完美转发的核心机制。

**问题：** 通用引用 `T&&` 收到参数后，无论原本是 lvalue 还是 rvalue，**参数 arg 本身永远是 lvalue**（因为它有名字）。如果直接传给下一层函数，会丢失值类别信息：

```cpp
template<typename T>
void wrapper(T&& arg) {
    target(arg);              // 永远以 lvalue 传给 target，rvalue 优化丢失
    target(std::forward<T>(arg)); // 保留值类别
}
```

**std::forward 的工作原理（reference collapsing 利用）：**

```cpp
// 情况 1：调用方传 lvalue x
wrapper(x);
// T 推导为 int&  →  static_cast<int& &&>(arg) → static_cast<int&>(arg) → lvalue

// 情况 2：调用方传 rvalue 42
wrapper(42);
// T 推导为 int   →  static_cast<int&&>(arg) → rvalue
```

**关键区别：**
- `std::move(x)` = 无条件转为 rvalue（用于自己确实要"移动"）
- `std::forward<T>(x)` = 条件转为 rvalue（用于把值类别向下传递）

**经典使用场景：**
```cpp
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```

A 错，forward 是条件的。C 错，forward 通常用在调用其他函数时传参。D 错，与引用计数无关。

**来源：** 字节 C++11/14/17 高级面试（参考：Effective Modern C++ Item 23、25）