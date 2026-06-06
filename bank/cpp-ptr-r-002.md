---
qid: cpp-ptr-r-002
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：数组名传参后 sizeof 退化

阅读以下代码，推断输出结果（假设 `sizeof(int)==4`，`sizeof(int*)==8`）：

```cpp
#include <iostream>
void print_size(int arr[]) {
    std::cout << sizeof(arr);
}
int main() {
    int a[10];
    std::cout << sizeof(a) << " ";
    print_size(a);
    return 0;
}
```

A. `40 40`  
B. `40 8`  
C. `8 8`  
D. 编译错误

## Explanation

正确答案是 B，即 `40 8`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
