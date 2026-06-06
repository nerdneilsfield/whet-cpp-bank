---
qid: cpp-friend-007
type: multi
kp: [cpp-friend]
difficulty: easy
answer_key: [A, C]
---

关于将 `operator<<` 重载为友元函数，哪些描述是正确的？（多选）

A. 因为左操作数是 `std::ostream&` 而非本类对象，所以不能定义为成员函数
B. 友元版本的 `operator<<` 性能优于成员函数版本
C. 友元 `operator<<` 可以访问类的私有成员，避免为每个字段提供 getter
D. 将 `operator<<` 声明为友元会导致封装性完全丧失，应避免
E. 声明为友元后，`cout << obj` 会自动转成 `obj.operator<<(cout)` 调用

## 解析

本题正确答案是 A, C。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。A 项正确：“因为左操作数是 std::ostream& 而非本类对象，所以不能定义为成员函数”符合题干要求；B 项错误：“友元版本的 operator<< 性能优于成员函数版本”与题干要求或 C++ 规则不符；C 项正确：“友元 operator<< 可以访问类的私有成员，避免为每个字段提供 getter”符合题干要求；D 项错误：“将 operator<< 声明为友元会导致封装性完全丧失，应避免 E. 声明为友元后，cout << obj 会自动转成 obj.operator<<(cout) 调用”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
