---
qid: cpp-algo-018
type: multi
kp: [cpp-algorithms]
difficulty: easy
answer_key: [A, C]
---

以下哪些说法关于 `std::for_each` 是**正确**的？（多选）

A. `std::for_each` 对范围内每个元素调用一次指定的函数/可调用对象
B. `std::for_each` 要求可调用对象必须返回 `bool` 类型
C. `std::for_each` 可以通过捕获外部变量的 lambda 对元素进行统计或副作用操作
D. `std::for_each` 会将操作结果写回原范围，等价于 `std::transform`

## 解析

正确答案是 A、C。`std::for_each` 会对区间内每个元素调用一次可调用对象，可调用对象不要求返回 `bool`。它常用于执行副作用，例如通过 lambda 捕获外部变量进行统计；若要把计算结果写入另一个区间，应使用 `std::transform`。
