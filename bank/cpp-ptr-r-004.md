---
qid: cpp-ptr-r-004
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：指针自增后再解引用

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int arr[] = {1, 2, 3, 4};
    int* p = arr;
    std::cout << *p++ << " ";
    std::cout << *p;
    return 0;
}
```

A. `2 2`  
B. `1 2`  
C. `1 1`  
D. `2 3`

## 解析

正确答案是 B，即 `1 2`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
