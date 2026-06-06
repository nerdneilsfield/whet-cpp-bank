---
qid: cpp-ub-signint-009
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: int
---

# `char` + `char` 的结果类型

下面代码中，表达式 `a + b` 的**类型**是什么？

```cpp
#include <iostream>
#include <typeinfo>
int main() {
    char a = 100;
    char b = 100;
    auto result = a + b;  // result 的类型？
    // 注意：200 超出了 signed char 的范围 [-128, 127]
    std::cout << result << std::endl;
    return 0;
}
```

`result` 的类型是：`______`

> **知识点**：**整数提升（Integer Promotion）**规则：`char`、`short` 等小于 `int` 的整数类型在参与算术运算前，会被自动提升为 `int`（或 `unsigned int`）。因此 `char + char` 的结果类型是 `int`，而非 `char`。`result` 为 `200`（int），不会溢出。若直接写 `char result = a + b;` 则会发生截断（200 超出 `signed char` 范围）。

## 解析

填入 `int`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
