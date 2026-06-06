---
qid: cpp-cf-002
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下代码的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int x = 0;
    if (x > 0)
        std::cout << "正数";
    else if (x < 0)
        std::cout << "负数";
    else
        std::cout << "零";
    return 0;
}
```

A. 正数
B. 负数
C. 零
D. 编译错误

## Explanation

正确答案为 C，因为“零”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
