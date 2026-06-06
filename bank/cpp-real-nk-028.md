---
qid: cpp-real-nk-028
type: single
kp: [cpp-cpp11, cpp-move-semantics, cpp-templates]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: A
tags: [interview-real, bytedance]
---

```cpp
template<typename T>
struct remove_reference { using type = T; };

template<typename T>
struct remove_reference<T&> { using type = T; };

template<typename T>
struct remove_reference<T&&> { using type = T; };

template<typename T>
constexpr T&& forward(remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}
```

`std::forward` 的核心原理是：

A. **通过引用折叠规则 + `static_cast<T&&>`**，当 T 为 X& 时返回 X&（左值引用），当 T 为 X 时返回 X&&（右值引用）
B. 运行时检查参数是左值还是右值，动态决定转成什么
C. 无条件地将实参转成右值引用
D. `T&&` 是万能引用，forward 只是类型安全的语法糖

---

**解析：**

完美转发的核心是**引用折叠**（reference collapsing）：

```
T&  &  → T&
T&  && → T&
T&& &  → T&
T&& && → T&&
```

对于 `forward`，当传进来的参数是左值时 T 推导为 `X&`（引用折叠后 `T&&` = `X&`），forward 中的 `static_cast<T&&>` 展开为 `static_cast<X&>`，保持左值。

当传进来的参数是右值时 T 推导为 `X`，forward 中的 `static_cast<T&&>` 展开为 `static_cast<X&&>`，返回右值引用。

B 错：全部是编译期确定，无运行时开销。
C 错：那是 `std::move` 而不是 `forward`。`move` 无条件转右值，`forward` 条件性转发。
D 错：虽然是语法糖，但关键是引用折叠的部分。

**来源：** 字节 C++ 模板面试题 / Effective Modern C++ Item 28

## Explanation

正确答案是 A。
完美转发的核心是引用折叠（reference collapsing）： 对于 forward，当传进来的参数是左值时 T 推导为 X&（引用折叠后 T&& = X&），forward 中的 static_cast<T&&> 展开为 static_cast<X&>，保持左值。
当传进来的参数是右值时 T 推导为 X，forward 中的 static_cast<T&&> 展开为 static_cast<X&&>，返回右值引用。
B 错：全部是编译期确定，无运行时开销。
