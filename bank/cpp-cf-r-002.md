---
qid: cpp-cf-r-002
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: A
---

# 代码阅读：do-while 条件初始为假

阅读以下代码，循环体被执行了几次？

```cpp
#include <iostream>
int main() {
    int n = 0;
    do {
        std::cout << "hello" << std::endl;
        n++;
    } while (n < 0);
    return 0;
}
```

A. 1 次
B. 0 次
C. 无限次
D. 编译错误

## Explanation

正确答案为 A，因为“1 次”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
