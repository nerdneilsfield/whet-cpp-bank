---
qid: cpp-scope-007
type: multi
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: [A, C]
---

# ODR（One Definition Rule）基础

关于 **ODR（One Definition Rule）**，下列说法哪些**正确**？（多选）

A. 同一程序中，每个非 inline 函数只能有一个定义
B. `inline` 函数也只能在一个翻译单元中定义
C. 同一翻译单元内，同一变量不能被定义两次
D. 类的定义可以在多个翻译单元中出现，且不受 ODR 约束
