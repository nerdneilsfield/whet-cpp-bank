---
qid: cpp-ub-signint-004
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# `unsigned i` 的循环条件永远为真

下面代码会发生什么？

```cpp
#include <iostream>
int main() {
    for (unsigned int i = 5; i >= 0; --i) {
        std::cout << i << " ";
    }
    return 0;
}
```

A. 无限循环（程序不会终止）
B. 输出 `5 4 3 2 1 0` 后正常退出
C. 输出 `5 4 3 2 1 0` 后因下溢崩溃
D. 编译错误

> **知识点**：`unsigned int` 永远 `>= 0`，循环条件 `i >= 0` 是**恒真式**（tautology）。当 `i == 0` 执行 `--i` 后，无符号下溢变为 `UINT_MAX`，循环继续。程序永远不会退出。编译器通常会为此发出警告。

## Explanation

正确答案是 A，即 无限循环（程序不会终止）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
