---
qid: cpp-ptr-013
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: C
---

`const int* p` 与 `int* const p` 的区别是？

A. 两者完全相同
B. `const int* p` 表示指针本身不可修改，`int* const p` 表示所指值不可修改
C. `const int* p` 表示所指值不可修改，`int* const p` 表示指针本身不可修改
D. 两者都表示既不能改指针也不能改值

## 解析

正确答案是 C，即 `const int* p` 表示所指值不可修改，`int* const p` 表示指针本身不可修改。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
