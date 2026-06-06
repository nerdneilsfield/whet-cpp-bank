---
qid: cpp-tmp-hard-006
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

C++17 fold 表达式中，左折叠与右折叠对于不满足结合律的运算结果不同。以下两个表达式：

```cpp
// 表达式 A（左折叠）
template<typename... Args>
auto left_fold(Args... args) {
    return (... - args);  // ((1 - 2) - 3)
}

// 表达式 B（右折叠）
template<typename... Args>
auto right_fold(Args... args) {
    return (args - ...);  // (1 - (2 - 3))
}

int a = left_fold(1, 2, 3);
int b = right_fold(1, 2, 3);
```

`a` 和 `b` 分别是？

A. `a = -4`，`b = 2`
B. `a = 2`，`b = -4`
C. `a = -4`，`b = -4`
D. `a = 2`，`b = 2`

## 解析

正确答案是 A，即 `a = -4`，`b = 2`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
