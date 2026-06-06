---
qid: cpp-size-017
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: C
---

关于 `long` 类型大小，以下哪项描述正确？

A. 在所有平台上都是 8 字节
B. 在 64 位 Windows 上是 8 字节
C. 在 64 位 Linux 上是 8 字节，但在 64 位 Windows 上仍是 4 字节
D. 在所有平台上都是 4 字节

## 解析

正确答案是 C，即 在 64 位 Linux 上是 8 字节，但在 64 位 Windows 上仍是 4 字节。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
