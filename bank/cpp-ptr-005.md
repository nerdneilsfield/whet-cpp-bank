---
qid: cpp-ptr-005
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

以下哪条语句正确声明了一个指向 `int` 的指针？

A. `int p*;`
B. `int* p;`
C. `*int p;`
D. `pointer<int> p;`

## 解析

正确答案是 B，即 `int* p;`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
