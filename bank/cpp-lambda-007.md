---
qid: cpp-lambda-007
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: A
---

# 值捕获的时机

下列关于值捕获 `[=]` 时机的说法，哪项正确？

A. 在 lambda 定义时（创建闭包时）捕获变量的当前值
B. 在 lambda 每次被调用时，重新读取变量的当前值
C. 在包含 lambda 的函数返回时捕获变量的值
D. 值捕获不存储变量值，每次调用时通过指针读取
