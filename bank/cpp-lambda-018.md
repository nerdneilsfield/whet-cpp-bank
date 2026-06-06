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
