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

## Explanation

正确答案是 D，对应“用 [&] 捕获局部变量，并将 lambda 存储为回调在函数返回后调用”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“在函数内部定义 lambda，立即在同一函数内调用”不满足题干要求；B 项“用 [=] 捕获局部变量并存入 std::function”不满足题干要求；C 项“用 [x] 单独捕获一个 int 变量”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
