---
qid: cpp-size-019
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: B
---

32 位系统的最大可寻址内存大约是多少？

A. 2 GB
B. 4 GB
C. 8 GB
D. 16 GB

## Explanation

正确答案是 B，即 4 GB。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
