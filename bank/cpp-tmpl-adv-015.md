---
qid: cpp-tmpl-adv-015
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: A
---

关于 SFINAE（C++11）和 `if constexpr`（C++17）的区别，以下说法正确的是？

A. SFINAE 通过模板替换失败来移除候选重载，作用于重载决议阶段；`if constexpr` 在编译期选择分支，写在函数体内，语法更简洁，是 C++17 引入的
B. 两者完全等价，`if constexpr` 只是 SFINAE 的语法糖，底层机制相同
C. SFINAE 是 C++17 特性，`if constexpr` 是 C++11 特性
D. `if constexpr` 可以完全替代所有 SFINAE 的用法，两者功能重叠无需区分

## 解析

正确答案是 A，即 SFINAE 通过模板替换失败来移除候选重载，作用于重载决议阶段；`if constexpr` 在编译期选择分支，写在函数体内，语法更简洁，是 C++17 引入的。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
