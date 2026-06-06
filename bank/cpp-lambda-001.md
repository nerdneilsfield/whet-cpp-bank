---
qid: cpp-lambda-001
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: C
---

# Lambda 基本语法结构

下列哪个选项是合法的 C++ lambda 表达式？

A. `[](int x) => x * 2`
B. `lambda(int x) { return x * 2; }`
C. `[](int x) { return x * 2; }`
D. `(int x) -> int { return x * 2; }`

## Explanation

正确答案是 C，对应“[](int x) { return x  2; }”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“[](int x) => x  2”不满足题干要求；B 项“lambda(int x) { return x  2; }”不满足题干要求；D 项“(int x) -> int { return x  2; }”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
