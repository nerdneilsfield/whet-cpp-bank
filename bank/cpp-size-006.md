---
qid: cpp-size-006
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: B
---

以下关于 `sizeof` 运算符返回类型的描述，哪项正确？

A. 返回 `int`（有符号整数）
B. 返回 `size_t`（无符号整数类型）
C. 返回 `long`
D. 返回 `ptrdiff_t`（有符号整数类型）

## Explanation

正确答案是 B，即 返回 `size_t`（无符号整数类型）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
