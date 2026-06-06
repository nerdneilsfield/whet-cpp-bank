---
qid: cpp-types-010
type: single
kp: [cpp-types]
difficulty: easy
answer_key: D
---
关于 `nullptr`，以下说法**正确**的是？

A. `nullptr` 与 `NULL` 完全相同，都是整数 0
B. `nullptr` 是 `int` 类型
C. `nullptr` 只能在 C++14 及以上使用
D. `nullptr` 是 `nullptr_t` 类型，专门表示空指针，不会与整数重载混淆

## 解析

正确答案是 D，即 `nullptr` 是 `nullptr_t` 类型，专门表示空指针，不会与整数重载混淆。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
