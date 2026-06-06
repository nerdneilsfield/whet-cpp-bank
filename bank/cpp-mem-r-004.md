---
qid: cpp-mem-r-004
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "C"
---

## 题目

以下代码有什么问题？

```cpp
#include <cstdlib>

int main() {
    int* p = new int(5);   // 分配单个 int
    delete[] p;            // 用 delete[] 释放
}
```

A. 没有问题，`delete[]` 可以兼容单对象指针
B. 内存泄漏，`p` 指向的内存没有被释放
C. 未定义行为：对非数组 `new` 的结果使用 `delete[]`
D. 编译错误，`delete[]` 不接受 `int*`

## 解析

C++ 标准规定：`new` 分配的对象必须用 `delete` 释放，`new[]` 分配的数组必须用 `delete[]` 释放。混用导致**未定义行为（UB）**，通常表现为堆损坏或崩溃。编译器不会报错，但行为不可预期。
