---
qid: cpp-size-024
type: single
kp: [cpp-type-sizes]
difficulty: easy
answer_key: D
---

以下代码在大多数平台上的行为是？

```cpp
int x = INT_MAX;
x = x + 1;
```

A. x 变为 INT_MIN（C++ 标准保证）
B. x 变为 0
C. 编译器报错
D. 未定义行为（Undefined Behavior）

## 解析

正确答案是 D，即 未定义行为（Undefined Behavior）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
