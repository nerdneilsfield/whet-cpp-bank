---
qid: cpp-size-007
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: D
---

在 64 位 Linux 平台上，`sizeof(long)` 通常为多少字节？

A. 2
B. 4
C. 6
D. 8

## Explanation

正确答案是 D，即 8。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
