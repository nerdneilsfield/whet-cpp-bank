---
qid: cpp-cf-004
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: D
---

以下 `switch` 语句的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int n = 2;
    switch (n) {
        case 1: std::cout << "one"; break;
        case 2: std::cout << "two"; break;
        case 3: std::cout << "three"; break;
        default: std::cout << "other";
    }
    return 0;
}
```

A. one
B. twothree
C. twoThreeother
D. two

## Explanation

正确答案为 D，因为“two”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
