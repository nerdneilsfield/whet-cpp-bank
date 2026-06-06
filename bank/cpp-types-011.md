---
qid: cpp-types-011
type: single
kp: [cpp-types]
difficulty: easy
answer_key: A
---
`unsigned int` 发生溢出时，C++ 标准规定的行为是？

A. 按 2^N 取模（环绕，well-defined）
B. 未定义行为（undefined behavior）
C. 产生编译错误
D. 结果截断为 0

## Explanation

正确答案是 A，即 按 2^N 取模（环绕，well-defined）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
