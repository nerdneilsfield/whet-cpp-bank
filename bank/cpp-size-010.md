---
qid: cpp-size-010
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: B
---

以下关于结构体 `sizeof` 的描述，哪项正确？

```cpp
struct S { char a; int b; };
```

A. `sizeof(S)` 一定等于 `sizeof(char) + sizeof(int)` = 5
B. `sizeof(S)` 可能大于 5，因为编译器可能在成员之间插入对齐填充
C. `sizeof(S)` 一定等于 8
D. `sizeof(S)` 的结果无法在编译期确定

## Explanation

正确答案是 B，即 `sizeof(S)` 可能大于 5，因为编译器可能在成员之间插入对齐填充。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
