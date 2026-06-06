---
qid: cpp-ub-signint-013
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# `char c = 255; if (c == 255)` 的结果

下面代码在 `char` **有符号**（`signed char`）的平台上输出什么？

```cpp
#include <iostream>
int main() {
    char c = 255;           // 255 超出 signed char 范围 [−128, 127]
    if (c == 255) {
        std::cout << "equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
    return 0;
}
```

（假设 `char` 为 `signed char`，8位，二进制补码）

A. `equal`（255 == 255）
B. 编译错误
C. `not equal`（`c` 存储为 -1，`-1 != 255`）
D. 未定义行为，结果不可预测

> **知识点**：在 `signed char` 平台上，`char c = 255` 是**实现定义行为**（因为 255 超出 `signed char` 的范围），通常截断为 `-1`（0xFF 的有符号解释）。比较 `c == 255` 时，`c`（-1）整数提升为 `int(-1)`，而 `255` 是 `int(255)`，`-1 != 255`，输出 `not equal`。`char` 的有无符号性是平台相关的，这里明确假设为有符号。

## 解析

正确答案是 C，即 `not equal`（`c` 存储为 -1，`-1 != 255`）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
