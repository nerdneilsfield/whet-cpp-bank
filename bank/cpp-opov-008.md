---
qid: cpp-opov-008
type: multi
kp: [cpp-operator-overload]
difficulty: easy
answer_key: [A, C, D]
---

以下关于 `operator[]` 的说法，**正确**的是哪几项？（多选）

A. 通常同时提供 `const` 和非 `const` 两个版本
B. 必须定义为非成员函数
C. 必须定义为成员函数
D. `const` 版本返回 `const` 引用，非 `const` 版本返回普通引用
E. 只能接受 `int` 类型下标

## Explanation

正确答案是 A, C, D。A 项 `通常同时提供 `const` 和非 `const` 两个版本` 符合规则；C 项 `必须定义为成员函数` 符合规则；D 项 ``const` 版本返回 `const` 引用，非 `const` 版本返回普通引用` 符合规则；B 项 `必须定义为非成员函数` 不满足该规则。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
