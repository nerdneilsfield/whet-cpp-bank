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
