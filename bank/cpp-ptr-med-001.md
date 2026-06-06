---
qid: cpp-ptr-med-001
type: single
kp: [cpp-arrays-pointers]
difficulty: medium
answer_key: A
---
下列代码输出是？

```cpp
#include <iostream>
void f(int arr[]) {
    std::cout << sizeof(arr) << "\n";
}
int main() {
    int arr[8];
    std::cout << sizeof(arr) << " ";
    f(arr);
    return 0;
}
```

A. 32 8
B. 32 32
C. 8 8
D. 64 8

---

**解析：**

在 `main` 中，`arr` 是 `int[8]`，`sizeof(arr)` 返回数组占用的总字节数：`8 * 4 = 32`（假设 `sizeof(int)=4`）。但在函数参数中，`int arr[]` 被调整为 `int* arr`（数组到指针的 decay），此时 `sizeof(arr)` 返回的是指针大小（64 位系统上为 8）。这就是数组在作为函数参数时“丢失大小信息”的根本原因——形参本质上是指针，不是数组。

## 解析

正确答案是 A，即 32 8。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
