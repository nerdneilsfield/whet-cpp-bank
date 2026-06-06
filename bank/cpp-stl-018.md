---
qid: cpp-stl-018
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

`std::array` 与 `std::vector` 最主要的区别是什么？

A. `std::array` 存储的元素类型只能是 `int`
B. `std::array` 的大小在**编译期**固定，`std::vector` 可以在运行时动态改变大小
C. `std::vector` 比 `std::array` 访问速度快
D. `std::array` 不能使用下标访问元素

## Explanation

正确答案是 B，即 `std::array` 的大小在**编译期**固定，`std::vector` 可以在运行时动态改变大小。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
