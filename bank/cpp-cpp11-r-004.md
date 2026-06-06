---
qid: cpp-cpp11-r-004
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，`arr` 的大小在编译期能否确定，程序输出是什么？

```cpp
#include <iostream>

constexpr int square(int n) {
    return n * n;
}

int main() {
    constexpr int sz = square(4);
    int arr[sz];                      // 行 A
    std::cout << sizeof(arr) / sizeof(int);
}
```

A. 编译通过，输出 `16`
B. 编译通过，输出 `4`
C. 编译错误：`square` 不能在常量表达式中调用
D. 运行时错误：VLA 不合法

## 解析

`constexpr` 函数在参数为常量时于编译期求值。`square(4)` 返回编译期常量 `16`，`sz` 为 `constexpr int`，可用作数组大小（非 VLA）。`sizeof(arr)/sizeof(int) = 16*4/4 = 16`。输出 `16`。
