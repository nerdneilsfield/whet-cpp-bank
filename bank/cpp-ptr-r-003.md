---
qid: cpp-ptr-r-003
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: D
---

# 代码阅读：const char* 字面量不可修改

阅读以下代码，下列说法正确的是：

```cpp
#include <iostream>
int main() {
    const char* s = "hello";
    s[0] = 'H';   // 行 A
    s = "world";  // 行 B
    std::cout << s;
    return 0;
}
```

A. 两行均合法，输出 `World`  
B. 行 A 合法，行 B 非法（指针本身是 `const`）  
C. 行 A、行 B 均合法，输出 `world`  
D. 行 A 非法（试图修改字符串字面量），行 B 合法

## Explanation

正确答案是 D，即 行 A 非法（试图修改字符串字面量），行 B 合法。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
