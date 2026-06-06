---
qid: cpp-ub-r-004
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

## 题目

下面代码可能产生什么后果？

```cpp
#include <iostream>

int main() {
    int arr[3] = {1, 2, 3};
    int x = 0;
    arr[5] = 99;   // 越界写
    std::cout << "x=" << x << std::endl;
    return 0;
}
```

A. 输出 `x=0`，越界写入不影响其他变量
B. 数组越界是未定义行为，`x` 可能被覆盖为 `99`，也可能崩溃
C. 编译错误，数组不允许越界访问
D. 输出 `x=99`，`arr[5]` 总是覆盖紧邻的局部变量

## 答案

B

## 解析

C++ 数组越界写入是**未定义行为**。`arr[5]` 超出 `arr` 的合法范围（下标 0–2），写入的地址取决于栈布局。如果 `x` 恰好被分配在 `arr[5]` 对应的内存位置，`x` 会被覆盖为 `99`；也可能破坏返回地址、其他变量或导致段错误。行为完全依赖编译器、优化级别和平台，不可预期。
