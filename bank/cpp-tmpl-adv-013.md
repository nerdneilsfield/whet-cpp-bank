---
qid: cpp-tmpl-adv-013
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

关于 `std::enable_if<condition, T>::type`，当 `condition` 为 `false` 时会发生什么？

A. 编译报错，提示条件不满足
B. 该重载仍然保留，但调用时抛出运行时异常
C. 该 `::type` 不存在，导致模板替换失败，该重载从候选集中被静默移除（SFINAE）
D. 返回 `void` 类型

## Explanation

正确答案是 C，即 该 `::type` 不存在，导致模板替换失败，该重载从候选集中被静默移除（SFINAE）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
