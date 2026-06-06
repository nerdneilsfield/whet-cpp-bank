---
qid: cpp-lambda-019
type: multi
kp: [cpp-lambdas]
difficulty: easy
answer_key: [A, C]
---

# 关于 mutable lambda 的正确说法

下列关于 `mutable` lambda 的说法，哪些正确？（多选）

A. `mutable` 关键字写在参数列表之后，函数体之前
B. 加了 `mutable` 后，对值捕获副本的修改会同步回外部变量
C. 不加 `mutable` 时，值捕获的变量在 lambda 内部视为 `const`，不可修改
D. `mutable` lambda 只能使用值捕获 `[=]`，不能混合捕获
E. 加了 `mutable` 后，lambda 自动变为引用捕获

## Explanation

本题正确答案是 A, C。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。A 项正确：“mutable 关键字写在参数列表之后，函数体之前”符合题干要求；B 项错误：“加了 mutable 后，对值捕获副本的修改会同步回外部变量”与题干要求或 C++ 规则不符；C 项正确：“不加 mutable 时，值捕获的变量在 lambda 内部视为 const，不可修改”符合题干要求；D 项错误：“mutable lambda 只能使用值捕获 [=]，不能混合捕获 E. 加了 mutable 后，lambda 自动变为引用捕获”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
