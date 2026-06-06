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

正确答案是 C，单对象 `new` 必须用单对象 `delete` 释放。把 `new int` 的结果交给 `delete[]` 会让运行时按数组分配格式处理内存，属于未定义行为。编译器通常无法仅凭 `int*` 类型区分它来自 `new` 还是 `new[]`，所以不一定报错。
