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
