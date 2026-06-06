---
qid: cpp-cf-001
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int x = 5;
    if (x > 3)
        std::cout << "A";
    else
        std::cout << "B";
    return 0;
}
```

A. B
B. A
C. AB
D. 无输出

## 解析

正确答案为 B，因为“A”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
