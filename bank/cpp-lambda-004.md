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

## Explanation

正确答案是 A，对应“[](int x) { return x  2; }”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：B 项“[x](int y) { return x + y; }”不满足题干要求；C 项“[&](int x) { return x  2; }”不满足题干要求；D 项“[=](int x) { return x  2; }”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
