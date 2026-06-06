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

## Explanation

本题正确答案是 A, C, D。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。A 项正确：“签名兼容的普通函数指针 int foo(int)”符合题干要求；B 项错误：“返回 void 的 lambda [](int x){ std::cout << x; }”与题干要求或 C++ 规则不符；C 项正确：“带值捕获的 lambda [n](int x){ return x + n; }（其中 n 为 int）”符合题干要求；D 项正确：“重载了 operator()(int) 返回 int 的仿函数对象 E. 成员函数指针（不绑定对象直接存储）”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
