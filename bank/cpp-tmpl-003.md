---
qid: cpp-tmpl-003
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: A
---

# 非类型模板参数

下列哪种声明使用了非类型模板参数？

A. `template<int N> struct Array { int data[N]; };`
B. `template<typename N> struct Array { int data[N]; };`
C. `template<class N> void print(N val);`
D. `template<type int> struct Array {};`

## 解析

正确答案是 A，即 `template<int N> struct Array { int data[N]; };`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
