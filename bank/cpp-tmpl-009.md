---
qid: cpp-tmpl-009
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

# std::pair 作为类模板示例

`std::pair<int, std::string> p(1, "hello");` 中，`std::pair` 是：

A. 一个普通类，接受构造函数参数
B. 一个函数模板，返回 pair 对象
C. 一个类模板，`<int, std::string>` 是模板参数
D. 一个宏，在预处理阶段展开

## 解析

正确答案是 C，即 一个类模板，`<int, std::string>` 是模板参数。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
