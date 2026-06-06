---
qid: cpp-taste-param-004
type: single
kp: [cpp-templates, cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: A
---

`make_widget` 是一个工厂函数，需要把入参"原样"传给 `Widget` 的构造函数。从**参数传递品味**的角度，哪段写得最好？

```cpp
// A
template <class... Args>
Widget make_widget(Args&&... args) {
    return Widget(std::forward<Args>(args)...);
}
```

```cpp
// B
template <class... Args>
Widget make_widget(Args... args) {
    return Widget(std::move(args)...);
}
```

```cpp
// C
template <class... Args>
Widget make_widget(const Args&... args) {
    return Widget(args...);
}
```

```cpp
// D
template <class... Args>
Widget make_widget(Args&&... args) {
    return Widget(std::move(args)...);
}
```

A. A 段：`Args&&` + `std::forward` 是完美转发的标准式，左值保左值、右值保右值。
B. B 段：按值接每个参数，再无脑 `std::move`，省掉了引用折叠的脑力负担。
C. C 段：`const&` 既不会拷贝也最安全，构造函数能自己决定要不要 move。
D. D 段：`Args&&` 已经是右值引用，直接 `std::move` 比 `std::forward` 更简洁。

## 解析

正确答案是 **A**。

- **A 段（好）**：万能引用（forwarding reference）+ `std::forward<Args>` 是"原样转发"的唯一正确写法。`Args&&` 在模板中是引用折叠语境下的万能引用：实参是左值就推为 `T&`，右值就推为 `T`，再用 `std::forward` 还原值类别。`std::make_unique`、`emplace_back` 都是这个模板。
- **B 段（差）**：按值接所有参数 = 先全部拷贝一份；再 `std::move` 只能补救"形参 → 构造"那一步。原本只该一次拷贝/移动的事现在变成"拷贝 + 移动"，热点路径上明显劣化。
- **C 段（差）**：丢掉了所有"传入是右值"的信息——可移动对象被强制按 `const&` 转发，最终一定走 `Widget` 的拷贝构造；想转发右值实参根本做不到。
- **D 段（错）**：`std::move` 把万能引用**无条件**转成右值，左值实参也被当右值搬空了——典型 forwarding bug，是 Scott Meyers 反复强调的反模式（见 Item 23/25）。

**核心识别点：**
- 完美转发只有一个标准式：模板 `Args&&` + `std::forward<Args>`。
- `std::move` 用于"我确定这是右值"，`std::forward` 用于"我保持调用者给我的值类别"。
- 在万能引用上写 `std::move` = 偷走调用者的左值，是隐式破坏性 bug。
- `Args&&` **只在模板里、未被替换的 `T&&`** 才是万能引用；具体类型的 `int&&` 是普通右值引用。

**来源：** Effective Modern C++ Item 23/25/30；cppreference forwarding reference 条目；`std::make_unique` 实现。
