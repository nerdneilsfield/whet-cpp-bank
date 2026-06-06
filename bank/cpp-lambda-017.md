---
qid: cpp-lambda-017
type: multi
kp: [cpp-lambdas]
difficulty: easy
answer_key: [A, C, D]
---

# std::function 可存储的可调用对象

`std::function<int(int)>` 可以存储哪些可调用对象？（多选）

A. 签名兼容的普通函数指针 `int foo(int)`
B. 返回 `void` 的 lambda `[](int x){ std::cout << x; }`
C. 带值捕获的 lambda `[n](int x){ return x + n; }`（其中 `n` 为 `int`）
D. 重载了 `operator()(int)` 返回 `int` 的仿函数对象
E. 成员函数指针（不绑定对象直接存储）
