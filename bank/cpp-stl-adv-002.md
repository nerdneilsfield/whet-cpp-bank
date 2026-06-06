---
qid: cpp-stl-adv-002
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

# std::array::size() 的编译期特性

关于 `std::array` 的 `size()` 方法，以下说法正确的是？

A. `size()` 返回的是编译期已知的常量，可以在 `constexpr` 上下文中使用
B. `size()` 与 `std::vector::size()` 完全相同，都在运行时计算
C. `std::array` 没有 `size()` 方法，只能用模板参数获取大小
D. `size()` 返回 `int` 类型

> **知识点**：`std::array<T, N>::size()` 是 `constexpr` 函数，返回编译期已知的 `N`，可用于模板参数、数组下标等编译期上下文。`std::vector::size()` 则是运行时值。返回类型是 `size_type`（无符号整数），不是 `int`。

## 解析

正确答案是 A，即 `size()` 返回的是编译期已知的常量，可以在 `constexpr` 上下文中使用。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
