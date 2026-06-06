---
qid: cpp-ub-011
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# use-after-free

```cpp
int* p = new int(42);
delete p;
int v = *p;   // 此行
```

标注行的行为是：

A. `v` 为 0，`delete` 会清零内存
B. 未定义行为（use-after-free），内存可能已被重用
C. 编译错误，`delete` 后指针变为 `nullptr`，不可解引用
D. 确定崩溃（段错误），属于可预测的运行时错误，不是 UB

## Explanation

正确答案是 B，即 未定义行为（use-after-free），内存可能已被重用。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
