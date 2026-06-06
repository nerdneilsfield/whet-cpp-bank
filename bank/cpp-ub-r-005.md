---
qid: cpp-ub-r-005
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

### 题目

下面代码的输出是什么？

```cpp
#include <iostream>

int main() {
    bool flag;   // 未初始化
    if (flag) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    return 0;
}
```

A. 总是输出 `false`，未初始化的 `bool` 默认为 `false`
B. 总是输出 `true`
C. 未初始化变量的读取是未定义行为，输出不确定，甚至可能两者都不输出
D. 编译错误，`bool` 必须初始化

## Explanation

C


读取**未初始化**的自动存储变量（如局部 `bool flag`）是**未定义行为**。`flag` 的底层字节包含栈上的随机垃圾值；若该字节不是合法的 `bool` 表示（0 或 1），某些硬件/ABI 或编译器优化可能产生奇异结果——例如同时进入 `if` 和 `else` 分支（在某些代码生成场景下理论上可能），或被优化掉分支。启用 `-Wuninitialized` 可获得编译器警告。
