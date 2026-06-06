---
qid: cpp-ub-001
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 哪种操作属于未定义行为

下列哪种操作在 C++ 标准中明确属于**未定义行为（Undefined Behavior）**？

A. 将 `unsigned int` 加到最大值后再加 1（发生回绕）
B. 有符号整数 `int` 相加后超出 `INT_MAX`
C. 对空 `std::vector` 调用 `size()`，得到 0
D. 用 `static_cast<double>(42)` 将整数转为浮点数

## Explanation

正确答案是 B，即 有符号整数 `int` 相加后超出 `INT_MAX`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
