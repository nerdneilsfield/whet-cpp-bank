---
qid: cpp-size-018
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: A
---

`size_t` 类型的大小与哪种类型保持一致？

A. 指针（`void*`）
B. `unsigned int`
C. `unsigned long long`
D. `int`

## Explanation

正确答案是 A，即 指针（`void*`）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
