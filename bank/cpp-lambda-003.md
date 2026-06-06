---
qid: cpp-lambda-003
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: D
---

# `mutable` lambda 的作用

下列关于 `mutable` lambda 的说法，哪项正确？

A. `mutable` 允许 lambda 修改引用捕获变量，否则编译报错
B. `mutable` 允许 lambda 访问外部变量，不加则不能捕获
C. `mutable` lambda 会将修改同步回外部的值捕获变量
D. `mutable` 允许 lambda 修改值捕获副本，但不影响外部原变量

## Explanation

正确答案是 D，对应“mutable 允许 lambda 修改值捕获副本，但不影响外部原变量”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“mutable 允许 lambda 修改引用捕获变量，否则编译报错”不满足题干要求；B 项“mutable 允许 lambda 访问外部变量，不加则不能捕获”不满足题干要求；C 项“mutable lambda 会将修改同步回外部的值捕获变量”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
