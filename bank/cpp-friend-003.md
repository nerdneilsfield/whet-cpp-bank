---
qid: cpp-friend-003
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: A
---

`friend` 函数与普通成员函数的本质区别是？

A. `friend` 函数没有隐式的 `this` 指针
B. `friend` 函数不能访问类的私有成员
C. `friend` 函数必须是全局函数，不能是另一个类的成员
D. `friend` 函数的调用语法与成员函数完全相同

## Explanation

正确答案是 A，对应“friend 函数没有隐式的 this 指针”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：B 项“friend 函数不能访问类的私有成员”不满足题干要求；C 项“friend 函数必须是全局函数，不能是另一个类的成员”不满足题干要求；D 项“friend 函数的调用语法与成员函数完全相同”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
