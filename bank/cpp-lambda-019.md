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
