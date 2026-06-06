---
qid: cpp-types-r-002
type: single
kp: [cpp-types]
difficulty: easy
answer_key: C
---

# 代码阅读：整数字面量溢出

以下代码的行为是什么？

```cpp
#include <iostream>
int main() {
    int x = 2147483648;
    std::cout << x << "\n";
}
```

A. 输出 `2147483648`  
B. 编译错误：字面量超出 `int` 范围  
C. 编译警告（溢出），输出 `-2147483648`（实现定义/UB，典型结果）  
D. 编译成功，输出 `0`
