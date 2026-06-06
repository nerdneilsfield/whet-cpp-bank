---
qid: cpp-ub-013
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 有符号溢出与编译器优化

```cpp
bool isPositiveAfterAdd(int x) {
    return x + 1 > x;  // 编译器可能优化为 return true
}
```

有符号整数溢出是______，因此编译器可以假设 `x + 1 > x` 永远成立并将函数优化为直接返回 `true`。

（填：未定义行为 / 实现定义行为 / 编译错误 / 合法操作）

## Explanation

填入 `未定义行为`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
