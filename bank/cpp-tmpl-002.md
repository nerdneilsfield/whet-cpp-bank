---
qid: cpp-tmpl-002
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

# typename 与 class 的等价性

关于模板参数关键字，下列说法正确的是？

A. `typename` 只能用于函数模板，`class` 只能用于类模板
B. `class` 表示参数必须是类类型，`typename` 允许基本类型
C. 在模板参数列表中，`typename T` 与 `class T` 完全等价
D. `typename` 是 C++17 才引入的新关键字

## 解析

正确答案是 C，即 在模板参数列表中，`typename T` 与 `class T` 完全等价。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
