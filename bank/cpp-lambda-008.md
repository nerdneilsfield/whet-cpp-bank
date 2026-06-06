---
qid: cpp-lambda-008
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: D
---

# 引用捕获的悬空引用风险

以下哪种场景最容易引发悬空引用（dangling reference）？

A. 在函数内部定义 lambda，立即在同一函数内调用
B. 用 `[=]` 捕获局部变量并存入 `std::function`
C. 用 `[x]` 单独捕获一个 `int` 变量
D. 用 `[&]` 捕获局部变量，并将 lambda 存储为回调在函数返回后调用
