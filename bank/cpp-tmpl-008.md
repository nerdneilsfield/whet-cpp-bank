---
qid: cpp-tmpl-008
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: A
---

# 模板特化概念

关于模板完整特化（full specialization），下列说法正确的是？

A. 可以为特定类型提供与泛化版本不同的实现，如 `template<> int max<int>(int, int)`
B. 模板特化会替换原模板，原模板将无法再使用
C. 函数模板不支持特化，只有类模板才支持
D. 特化后的版本必须与原模板具有相同的函数体

## Explanation

正确答案是 A，即 可以为特定类型提供与泛化版本不同的实现，如 `template<> int max<int>(int, int)`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
