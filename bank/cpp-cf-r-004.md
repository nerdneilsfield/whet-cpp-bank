---
qid: cpp-cf-r-004
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

# 代码阅读：嵌套循环 break 只跳内层

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1) break;
            std::cout << i << j << " ";
        }
    }
    return 0;
}
```

A. `00 01 02 10 11 12 20 21 22 `
B. `00 10 20 `
C. `00 `
D. 编译错误

## 解析

正确答案为 B，因为“`00 10 20 `”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
