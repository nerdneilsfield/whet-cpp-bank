---
qid: cpp-ub-008
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# 有符号整数溢出

```cpp
#include <climits>
int main() {
    int x = INT_MAX;
    int y = x + 1;   // 此行
    return 0;
}
```

标注行的行为是：

A. `y` 等于 `INT_MIN`，有符号溢出定义为回绕
B. 编译错误，编译器禁止溢出表达式
C. 未定义行为，编译器可假设溢出不发生并据此优化
D. 运行时会抛出 `std::overflow_error`

## Explanation

正确答案是 C，即 未定义行为，编译器可假设溢出不发生并据此优化。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
