---
qid: cpp-lambda-016
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: C
---

# 显式返回类型语法

下列 lambda 中，显式指定返回类型为 `double` 的写法正确的是？

A. `[](int x) : double { return x; }`
B. `[](int x) double { return x; }`
C. `[](int x) -> double { return x; }`
D. `[](int x) => double { return x; }`

## 解析

正确答案是 C，对应“[](int x) -> double { return x; }”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“[](int x) : double { return x; }”不满足题干要求；B 项“[](int x) double { return x; }”不满足题干要求；D 项“[](int x) => double { return x; }”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
