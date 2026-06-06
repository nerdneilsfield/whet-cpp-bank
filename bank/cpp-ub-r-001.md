---
qid: cpp-ub-r-001
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

### 题目

下面代码在开启优化（`-O2`）后可能出现什么现象？

```cpp
#include <iostream>

int main() {
    for (int i = 0; i >= 0; i++) {
        // 做一些工作
    }
    std::cout << "done" << std::endl;
    return 0;
}
```

A. 循环执行约 `2^31` 次后正常结束，输出 `done`
B. 循环立即结束，输出 `done`
C. 编译器假设有符号整数不溢出，将循环优化为无限循环，永不输出 `done`
D. 编译错误

## Explanation

C


C++ 标准规定**有符号整数溢出是未定义行为**。编译器在 `-O2` 下可以合法地假设 UB 不会发生，因此假设 `i` 永远不会溢出——即 `i >= 0` 恒为真，循环条件永不为假，进而将整个循环优化为无限循环。GCC/Clang 均有此优化实例。如需环绕语义，应使用无符号类型或 `-fwrapv` 编译选项。
