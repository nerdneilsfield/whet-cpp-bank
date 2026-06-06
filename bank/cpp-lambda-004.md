---
qid: cpp-lambda-004
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: A
---

# Lambda 转为函数指针

下列哪种 lambda 可以隐式转换为函数指针？

A. `[](int x) { return x * 2; }`
B. `[x](int y) { return x + y; }`
C. `[&](int x) { return x * 2; }`
D. `[=](int x) { return x * 2; }`
