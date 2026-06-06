---
qid: cpp-tmp-hard-008
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: C
---

以下代码使用 fold 表达式检查所有参数是否均为真：

```cpp
template<typename... Args>
bool all_true(Args... args) {
    return (args && ...);
}
```

调用 `all_true(true, 1, 0, true)` 的返回值是？

A. `true`
B. 编译错误，`&&` 不能用于 fold 表达式
C. `false`
D. 未定义行为

## 解析

正确答案是 C，即 `false`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
