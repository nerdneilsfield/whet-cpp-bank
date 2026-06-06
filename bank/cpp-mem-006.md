---
qid: cpp-mem-006
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: C
---

# 悬空指针（dangling pointer）是指？

A. 值为 `nullptr` 的指针
B. 指向栈变量的指针
C. 指向已经被释放（或已超出生命周期）的内存的指针
D. 未初始化的指针变量

<!--
悬空指针：指向的内存已被释放，指针本身仍存在但所指内容无效。
nullptr 是空指针，不是悬空指针。答案 C。
-->
