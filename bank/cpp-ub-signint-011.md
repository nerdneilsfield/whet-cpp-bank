---
qid: cpp-ub-signint-011
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# `short` 参与算术自动提升为 `int`

下面代码中，哪个断言**不会**失败（即为真）？

```cpp
#include <iostream>
#include <type_traits>
int main() {
    short a = 1000;
    short b = 2000;
    auto  c = a + b;

    // 以下哪条为 true？
    bool t1 = std::is_same_v<decltype(c), short>;   // A 的反面
    bool t2 = std::is_same_v<decltype(c), int>;     // B
    bool t3 = (sizeof(c) == sizeof(short));          // C
    bool t4 = std::is_same_v<decltype(c), long>;    // D

    std::cout << t1 << t2 << t3 << t4 << std::endl;
    return 0;
}
```

输出的四个值中，哪一个为 `1`？

A. `t2`（`decltype(c)` 是 `int`）
B. `t1`（`decltype(c)` 是 `short`）
C. `t3`（`sizeof(c) == sizeof(short)`）
D. `t4`（`decltype(c)` 是 `long`）

> **知识点**：`short` 参与算术运算时被**整数提升**为 `int`。因此 `a + b` 的结果类型是 `int`，`sizeof(c)` 为 4（而非 2）。`t2` 为真，输出 `0100`。

## 解析

正确答案是 A，即 `t2`（`decltype(c)` 是 `int`）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
