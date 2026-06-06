---
qid: cpp-ub-signint-012
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: -1
---

# `~uint8_t(0)` 的结果类型和值

下面代码输出什么？

```cpp
#include <iostream>
#include <cstdint>
int main() {
    uint8_t x = 0;
    auto result = ~x;    // 按位取反
    std::cout << result << std::endl;
    return 0;
}
```

请填写输出值：`______`

> **知识点**：`uint8_t`（即 `unsigned char`）在按位取反前，先被**整数提升**为 `int`（有符号）。`x = 0`，提升为 `int(0)` 后取反得 `~0 = -1`（所有位为1的有符号 int）。因此输出 `-1`，而非 `255`。若结果类型是 `uint8_t`，`~0` 应为 `255`，但提升使类型变为 `int`。要得到 `255`，需要写 `(uint8_t)~x` 或 `x ^ 0xFF`。

## Explanation

填入 `-1`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
