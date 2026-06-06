---
qid: cpp-tmpl-adv-003
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

以下关于 `std::is_pointer` 的说法，正确的是？

A. `std::is_pointer<int*>::value` 为 `false`，`std::is_pointer<int>::value` 为 `true`
B. 两者均为 `true`
C. `std::is_pointer<int*>::value` 为 `true`，`std::is_pointer<int>::value` 为 `false`
D. 两者均为 `false`

## Explanation

正确答案是 C，即 `std::is_pointer<int*>::value` 为 `true`，`std::is_pointer<int>::value` 为 `false`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
