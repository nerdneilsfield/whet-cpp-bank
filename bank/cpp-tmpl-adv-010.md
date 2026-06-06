---
qid: cpp-tmpl-adv-010
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

在可变参数模板中，`f(args...)` 和 `f(args)...` 有何区别？

A. 两者等价，写法不同但效果一样
B. `f(args...)` 将整个参数包作为参数列表传给 `f`；`f(args)...` 对包中每个元素单独调用 `f` 并展开（包展开表达式，常用于初始化列表等上下文）
C. `f(args...)` 只能用于函数调用，`f(args)...` 只能用于模板实参列表
D. `f(args)...` 是错误语法，C++ 不支持这种写法
