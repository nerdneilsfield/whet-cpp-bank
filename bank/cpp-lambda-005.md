---
qid: cpp-lambda-005
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: C
---

# `std::function` 的用途

关于 `std::function<int(int)>`，下列说法正确的是？

A. 只能存储 lambda 表达式，不能存储普通函数
B. 性能与直接调用函数指针完全相同，无任何开销
C. 可以存储任意签名兼容的可调用对象，包括 lambda、函数指针和仿函数
D. 模板参数 `int(int)` 表示返回 `int` 且接受 `int` 类型引用的函数
