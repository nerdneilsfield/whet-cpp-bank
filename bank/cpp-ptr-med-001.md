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