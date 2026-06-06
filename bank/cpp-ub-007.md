---
qid: cpp-ub-007
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# 空指针解引用

```cpp
int* p = nullptr;
int v = *p;
```

上述代码的行为是：

A. 编译错误，`nullptr` 不能被解引用
B. 未定义行为，结果不可预测
C. 确定崩溃（Segfault），属于可预测的运行时错误，不是 UB
D. `v` 被初始化为 0，因为 `nullptr` 地址为 0

## Explanation

正确答案是 B，即 未定义行为，结果不可预测。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
