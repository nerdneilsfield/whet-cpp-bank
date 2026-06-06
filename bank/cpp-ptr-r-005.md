---
qid: cpp-ptr-r-005
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：引用绑定后的别名效果

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int x = 10;
    int& r = x;
    r = 20;
    std::cout << x << " " << r;
    return 0;
}
```

A. `20 20`  
B. `10 20`  
C. `20 10`  
D. `10 10`

## 解析

正确答案是 A，即 `20 20`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
