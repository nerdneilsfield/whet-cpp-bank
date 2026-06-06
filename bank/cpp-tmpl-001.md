---
qid: cpp-tmpl-001
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 函数模板语法

下列哪种写法是正确的函数模板声明？

A. `template<T> T max(T a, T b);`
B. `template<typename T> T max(T a, T b);`
C. `template T max(T a, T b);`
D. `typename<T> T max(T a, T b);`

## 解析

正确答案是 B，即 `template<typename T> T max(T a, T b);`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
