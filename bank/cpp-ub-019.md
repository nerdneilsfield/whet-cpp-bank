---
qid: cpp-ub-019
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: D
---

# 无符号整数溢出 vs 有符号整数溢出

```cpp
unsigned int u = 0;
u = u - 1;        // 行 A

int s = INT_MIN;
s = s - 1;        // 行 B
```

关于两行的行为，正确的说法是：

A. 两行都是未定义行为
B. 行 A 是未定义行为，行 B 是合法回绕
C. 两行都是合法的取模回绕
D. 行 A 合法（`unsigned` 溢出结果为 `UINT_MAX`，标准明确规定回绕），行 B 是未定义行为

## 解析

正确答案是 D，即 行 A 合法（`unsigned` 溢出结果为 `UINT_MAX`，标准明确规定回绕），行 B 是未定义行为。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
