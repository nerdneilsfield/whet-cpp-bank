---
qid: cpp-ub-signint-010
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# `unsigned char` 位运算后的类型

下面代码中，`result` 的类型是什么？

```cpp
#include <iostream>
int main() {
    unsigned char x = 0xF0;
    unsigned char y = 0x0F;
    auto result = x | y;   // result 的类型？
    std::cout << sizeof(result) << std::endl;
    return 0;
}
```

A. `unsigned char`，`sizeof` 输出 `1`
B. `int`，`sizeof` 输出 `4`
C. `unsigned int`，`sizeof` 输出 `4`
D. 取决于编译器实现

> **知识点**：`unsigned char` 在参与位运算（`|`、`&`、`^`、`~`）前，同样会经过**整数提升**，提升为 `int`（因为 `unsigned char` 的值范围可以被 `int` 完整表示）。所以 `x | y` 的结果类型是 `int`，`sizeof` 输出 `4`。这与直觉（"两个 unsigned char 按位或，结果应该是 unsigned char"）相悖。
