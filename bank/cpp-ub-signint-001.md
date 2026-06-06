---
qid: cpp-ub-signint-001
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# 有符号/无符号比较：`-1 > 2u` 的结果

下面代码的输出是什么？

```cpp
#include <iostream>
int main() {
    int a = -1;
    unsigned int b = 2u;
    std::cout << (a > b) << std::endl;
    return 0;
}
```

A. `1`（即 true）
B. `0`（即 false）
C. 未定义行为，结果不可预测
D. 编译错误

> **知识点**：有符号与无符号整数混合比较时，有符号操作数会被**隐式转换为无符号类型**。`-1` 转为 `unsigned int` 后变为 `UINT_MAX`（4294967295），远大于 `2u`，因此比较结果为 `true`（1）。

## 解析

正确答案是 A，即 `1`（即 true）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
