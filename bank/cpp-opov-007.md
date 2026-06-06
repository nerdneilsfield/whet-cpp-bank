---
qid: cpp-opov-007
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: A
---

`operator+=` 按照惯例应返回什么？

A. `*this` 的引用（`T&`）
B. `*this` 的副本（按值返回）
C. `void`
D. `const T&`

## 解析

正确答案是 A，因为该选项对应 ``*this` 的引用（`T&`）`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
