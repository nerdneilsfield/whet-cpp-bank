---
qid: cpp-size-021
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: C
---

`unsigned char` 的取值范围是？

A. -128 ~ 127
B. -127 ~ 128
C. 0 ~ 255
D. 0 ~ 127

## Explanation

正确答案是 C，即 0 ~ 255。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
