---
qid: cpp-lambda-020
type: multi
kp: [cpp-lambdas]
difficulty: easy
answer_key: [B, C, D]
---

# Lambda 与 std::function 综合判断

以下关于 lambda 和 `std::function` 的说法，哪些正确？（多选）

A. `std::function` 调用开销与直接调用函数指针完全相同
B. 无捕获 lambda 体积最小，有捕获 lambda 会在闭包中存储捕获的变量
C. 引用捕获 lambda 的生命周期不得超过被捕获变量的生命周期
D. 立即调用 lambda `[](){ return 42; }()` 是合法的 C++ 表达式
E. `std::function` 无法存储带状态（有捕获）的 lambda

## 解析

本题正确答案是 B, C, D。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。A 项错误：“std::function 调用开销与直接调用函数指针完全相同”与题干要求或 C++ 规则不符；B 项正确：“无捕获 lambda 体积最小，有捕获 lambda 会在闭包中存储捕获的变量”符合题干要求；C 项正确：“引用捕获 lambda 的生命周期不得超过被捕获变量的生命周期”符合题干要求；D 项正确：“立即调用 lambda [](){ return 42; }() 是合法的 C++ 表达式 E. std::function 无法存储带状态（有捕获）的 lambda”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
