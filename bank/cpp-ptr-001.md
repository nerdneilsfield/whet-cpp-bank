---
qid: cpp-ptr-001
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

以下哪种方式正确声明并初始化一个包含 3 个整数的数组？

A. `int arr[3] = {1, 2, 3, 4};`
B. `int arr[3] = {1, 2, 3};`
C. `int arr[] ;`
D. `int [3]arr = {1, 2, 3};`

## Explanation

正确答案是 B，即 `int arr[3] = {1, 2, 3};`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
