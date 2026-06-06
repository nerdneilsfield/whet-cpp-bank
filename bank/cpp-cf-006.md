---
qid: cpp-cf-006
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下 `for` 循环共输出多少个数字？

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 5; i++) {
        std::cout << i << " ";
    }
    return 0;
}
```

A. 4
B. 6
C. 5
D. 0

## Explanation

正确答案为 C，因为“5”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
