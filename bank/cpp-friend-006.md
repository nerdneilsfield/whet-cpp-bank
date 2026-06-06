---
qid: cpp-friend-006
type: multi
kp: [cpp-friend]
difficulty: easy
answer_key: [B, D]
---

关于友元类（`friend class`），下列说法哪些正确？（多选）

A. `friend class B;` 声明后，B 中的私有成员也对 A 自动开放（互相透明）
B. `friend class B;` 声明后，B 的所有成员函数都可以访问 A 的私有成员
C. 友元类关系是对称的，在 A 中声明 `friend class B` 后，A 也自动成为 B 的友元
D. 若只在 A 中声明 `friend class B`，则 B 可访问 A 的私有成员，但 A 不能访问 B 的私有成员
E. 友元类关系可以跨多层继承自动传播

## 解析

本题正确答案是 B, D。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。A 项错误：“friend class B; 声明后，B 中的私有成员也对 A 自动开放（互相透明）”与题干要求或 C++ 规则不符；B 项正确：“friend class B; 声明后，B 的所有成员函数都可以访问 A 的私有成员”符合题干要求；C 项错误：“友元类关系是对称的，在 A 中声明 friend class B 后，A 也自动成为 B 的友元”与题干要求或 C++ 规则不符；D 项正确：“若只在 A 中声明 friend class B，则 B 可访问 A 的私有成员，但 A 不能访问 B 的私有成员 E. 友元类关系可以跨多层继承自动传播”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
