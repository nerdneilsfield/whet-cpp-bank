---
qid: cpp-func-r-005
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：无终止条件的递归

以下代码运行后会发生什么？

```cpp
#include <iostream>
int sum(int n) {
    return n + sum(n - 1);  // 没有 base case
}
int main() {
    std::cout << sum(5);
    return 0;
}
```

A. 输出 `15`
B. 输出 `0`
C. 运行时栈溢出（stack overflow），程序崩溃
D. 编译失败，编译器检测到无限递归
