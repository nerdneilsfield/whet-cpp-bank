---
qid: cpp-stl-adv-001
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# std::array 声明语法

以下哪种声明方式是正确的 `std::array` 用法？

```cpp
#include <array>
```

A. `std::array<int> arr = {1, 2, 3};`
B. `std::array arr<int, 3> = {1, 2, 3};`
C. `std::array<int, 3> arr = {1, 2, 3};`
D. `std::array<int, n> arr = {1, 2, 3};`（其中 `n` 是运行时变量）

> **知识点**：`std::array` 的第二个模板参数是数组大小，必须是编译期常量（`constexpr` 或字面量），不能是运行时变量。选项 A 缺少大小参数，D 中 `n` 为运行时变量，均无法编译。

## 解析

正确答案是 C，即 `std::array<int, 3> arr = {1, 2, 3};`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
