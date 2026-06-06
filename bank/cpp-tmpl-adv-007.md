---
qid: cpp-tmpl-adv-007
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

以下关于可变参数模板语法 `template<typename... Args>` 的说法，正确的是？

A. `Args` 是一个类型，只能代表一个模板参数
B. `...` 必须紧跟在 `typename` 之前，不能放在 `Args` 之后
C. `Args` 是一个参数包（parameter pack），可以匹配零个或多个类型
D. 可变参数模板只能用于函数模板，不能用于类模板

## Explanation

正确答案是 C，即 `Args` 是一个参数包（parameter pack），可以匹配零个或多个类型。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
