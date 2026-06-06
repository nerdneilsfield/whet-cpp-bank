---
qid: cpp-opov-005
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: B
---

后置 `++` 运算符重载与前置 `++` 的函数签名区别是什么？

A. 后置版本函数名为 `operator++()`，前置版本函数名为 `operator++(int)`
B. 后置版本多一个 `int` 类型的哑参数：`operator++(int)`
C. 两者签名完全相同，靠返回类型区分
D. 后置版本必须是非成员函数
