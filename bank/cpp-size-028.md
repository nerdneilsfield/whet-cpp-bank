---
qid: cpp-size-028
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: A
---

`float` 的有效十进制精度约为多少位，`double` 约为多少位？

A. float 约 7 位，double 约 15~16 位
B. float 约 10 位，double 约 20 位
C. float 约 7 位，double 约 10 位
D. float 约 6 位，double 约 12 位

## Explanation

正确答案是 A，即 float 约 7 位，double 约 15~16 位。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
