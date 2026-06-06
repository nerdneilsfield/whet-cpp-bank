---
qid: cpp-tmpl-adv-002
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

`std::is_integral<int>::value` 和 `std::is_integral<float>::value` 的值分别是？

A. `false` 和 `true`
B. `true` 和 `false`
C. `true` 和 `true`
D. `false` 和 `false`

## Explanation

正确答案是 B，即 `true` 和 `false`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
