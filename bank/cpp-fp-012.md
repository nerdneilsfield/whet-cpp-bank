---
qid: cpp-fp-012
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: C
---

# 代码阅读：函数指针数组（跳转表）

```cpp
#include <iostream>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int sub(int a, int b) { return a - b; }

int (*ops[3])(int, int) = {add, mul, sub};

int main() {
    std::cout << ops[1](3, 4);
}
```

输出是？

A. 7  
B. 1  
C. 12  
D. 编译错误  
