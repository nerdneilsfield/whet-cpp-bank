---
qid: cpp-ptr-004
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: A
---

以下代码的输出是？

```cpp
int arr[] = {5, 10, 15};
int* p = arr;
std::cout << *p;
```

A. 5
B. 10
C. 15
D. 编译错误

## 解析

正确答案是 A，即 5。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
