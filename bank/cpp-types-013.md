---
qid: cpp-types-013
type: single
kp: [cpp-types]
difficulty: easy
answer_key: C
---
`constexpr int N = 42;` 与 `const int N = 42;` 的**主要区别**是？

A. 两者完全相同，可互换
B. `constexpr` 只能用于全局变量
C. `constexpr` 保证值在**编译期**求值，可用于模板参数和数组大小
D. `const` 比 `constexpr` 更严格

## Explanation

正确答案是 C，即 `constexpr` 保证值在**编译期**求值，可用于模板参数和数组大小。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
