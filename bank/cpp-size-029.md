---
qid: cpp-size-029
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: B
---

x86/x64 架构使用哪种字节序？

A. 大端（big-endian）
B. 小端（little-endian）
C. 混合端（middle-endian）
D. 取决于操作系统

## 解析

正确答案是 B，即 小端（little-endian）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
