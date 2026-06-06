---
qid: cpp-opov-019
type: multi
kp: [cpp-operator-overload]
difficulty: easy
answer_key: [A, C, E]
---

以下关于运算符重载的说法，**正确**的有哪几项？（多选）

A. `operator()` 可以定义为成员函数，使对象像函数一样被调用
B. 重载 `+` 后，`a + b + c` 的运算顺序可以被改变
C. `operator<<` 若需访问类的私有成员，通常声明为友元函数
D. 后置 `++` 返回的是修改后的对象引用
E. `explicit operator bool()` 可防止隐式转换到 `int` 等其他整数类型
