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
