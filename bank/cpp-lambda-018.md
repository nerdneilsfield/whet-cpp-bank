---
qid: cpp-lambda-018
type: multi
kp: [cpp-lambdas]
difficulty: easy
answer_key: [B, D]
---

# 以下哪些 lambda 能隐式转换为函数指针

下列哪些 lambda 可以隐式转换为对应的函数指针类型？（多选）

A. `[x](int y) { return x + y; }`（`x` 为外部 `int`）
B. `[](int a, int b) { return a + b; }`
C. `[&](int x) { return x; }`
D. `[](double d) -> int { return (int)d; }`
E. `[=](int x) { return x; }`

## 解析

本题正确答案是 B, D。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。A 项错误：“[x](int y) { return x + y; }（x 为外部 int）”与题干要求或 C++ 规则不符；B 项正确：“[](int a, int b) { return a + b; }”符合题干要求；C 项错误：“[&](int x) { return x; }”与题干要求或 C++ 规则不符；D 项正确：“[](double d) -> int { return (int)d; } E. [=](int x) { return x; }”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
