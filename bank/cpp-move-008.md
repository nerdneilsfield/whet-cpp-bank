---
qid: cpp-move-008
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: A
---

# std::forward 的用途

`std::forward<T>(arg)` 的主要用途是？

A. 在模板函数中将参数以原始值类别（lvalue/rvalue）转发给另一个函数
B. 将参数强制转换为右值引用
C. 将参数复制并传递给另一个函数
D. 检查参数是否为右值

## 解析

正确答案是 A，`std::forward<T>(arg)` 用于完美转发，依据模板参数 `T` 恢复原始实参的左值/右值类别。它和 `std::move` 不同，后者无条件把表达式转成右值。没有 `forward` 时，具名形参即使类型是 `T&&`，在表达式中也会作为左值传递。
