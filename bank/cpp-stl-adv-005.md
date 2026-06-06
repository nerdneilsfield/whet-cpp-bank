---
qid: cpp-stl-adv-005
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: D
---

# std::array 传函数不退化为指针

```cpp
#include <array>
#include <iostream>

void printSize(std::array<int, 5> arr) {
    std::cout << arr.size() << std::endl;
}

void printSizeRaw(int* arr) {
    // 无法在这里知道数组真实大小
}
```

将 `std::array<int, 5>` 传入函数时，以下说法正确的是？

A. 与传原生数组一样，会退化为指针，函数内无法用 `size()` 获取大小
B. 传入后 `arr.size()` 返回指针大小（通常为 8）
C. `std::array` 不能按值传参，必须传引用
D. 函数内 `arr.size()` 正确返回 5，不会退化为指针

> **知识点**：原生数组传参时退化为指针，丢失长度信息。`std::array` 是真正的对象，按值传参时完整拷贝，`size()` 仍返回正确的编译期大小 5。为避免拷贝开销，实践中通常传 `const std::array<int,5>&`，但语义上不退化。

## 解析

正确答案是 D，即 函数内 `arr.size()` 正确返回 5，不会退化为指针。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
