---
qid: cpp-scope-r-001
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

## 题目

下面代码连续调用 `counter()` 三次，输出是什么？

```cpp
#include <iostream>

void counter() {
    static int n = 0;
    ++n;
    std::cout << n << "\n";
}

int main() {
    counter();
    counter();
    counter();
}
```

A. 0 0 0
B. 1 1 1
C. 1 2 3
D. 编译错误

## 答案

C

## 解析

`static` 局部变量只初始化一次（程序第一次执行到该语句时），之后在函数调用之间保持值。每次调用 `counter()` 时 `n` 都在上一次的基础上递增，因此输出 1、2、3。
