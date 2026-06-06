---
qid: cpp-tmpl-014
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

# 显式模板参数解决冲突

```cpp
template<typename T>
T max(T a, T b) { return a > b ? a : b; }
```

要用 `1` 和 `2.0` 调用 `max` 且让 `T=double`，正确写法是？

A. `max(1, 2.0)`
B. `max<>(1, 2.0)`
C. `max<double>(1, 2.0)`
D. `max(double(1), 2.0)` 不行，只能用显式模板参数

## 解析

正确答案是 C，即 `max<double>(1, 2.0)`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
