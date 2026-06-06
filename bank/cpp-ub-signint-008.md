---
qid: cpp-ub-signint-008
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# signed/unsigned 混合算术的提升规则

下面代码的输出是什么？

```cpp
#include <iostream>
int main() {
    int    a = -3;
    unsigned int b = 1u;
    auto   c = a + b;   // c 的类型是什么？值是什么？
    std::cout << c << std::endl;
    return 0;
}
```

A. `-2`（int 类型，-3 + 1 = -2）
B. 未定义行为
C. `4294967294`（unsigned int，`(UINT_MAX+1) - 3 + 1 = UINT_MAX - 1`）
D. 编译错误

> **知识点**：当 `int` 与 `unsigned int` 混合运算时，**通常算术转换（Usual Arithmetic Conversions）**规定：`int` 被提升为 `unsigned int`。`-3` 转为 `unsigned int` 变为 `4294967293`，加 `1` 得 `4294967294`。结果类型为 `unsigned int`，而非 `int`。`auto c` 会推导为 `unsigned int`。

## 解析

正确答案是 C，即 `4294967294`（unsigned int，`(UINT_MAX+1) - 3 + 1 = UINT_MAX - 1`）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
