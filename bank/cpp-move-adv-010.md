---
qid: cpp-move-adv-010
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: B
---

关于 `std::forward<T>(arg)` 的行为，下列描述**正确**的是？

```cpp
template<typename T>
void wrapper(T&& arg) {
    target(std::forward<T>(arg));  // (X)
    // 等价于：
    // 当 T = int&  时，forward 返回 int&  (lvalue ref)
    // 当 T = int   时，forward 返回 int&& (rvalue ref)
}
```

A. `std::forward<T>(arg)` 等价于 `std::move(arg)`，总是产生右值引用
B. 当 T 是引用类型时，`std::forward<T>(arg)` 返回左值引用；当 T 是非引用类型时，返回右值引用
C. `std::forward` 不依赖 T 的类型，始终转发为左值
D. `std::forward<T>(arg)` 只在 T 为右值引用时才有效，否则编译报错

---

**解析：**

`std::forward<T>(arg)` 的语义：
- **T 是引用类型**（如 `int&`，说明原始实参是左值）：转型为左值引用，等价于 `static_cast<T&>(arg)`。
- **T 是非引用类型**（如 `int`，说明原始实参是右值）：转型为右值引用，等价于 `static_cast<T&&>(arg)`。

这正好"还原"了原始实参的值类别（value category），这就是"完美转发"的含义。选 B。

`std::move` 与之不同——它**无条件**转型为右值引用，不区分原始值类别。
