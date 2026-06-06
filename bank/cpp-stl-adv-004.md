---
qid: cpp-stl-adv-004
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# std::array 整体赋值

```cpp
#include <array>

std::array<int, 3> a = {1, 2, 3};
std::array<int, 3> b = {4, 5, 6};
int c[3] = {7, 8, 9};
int d[3] = {10, 11, 12};
```

以下哪条语句能正确编译并完成整体赋值？

A. `c = d;`
B. `c = a;`（将 `std::array` 赋给原生数组）
C. `a = b;`
D. `a = c;`（将原生数组赋给 `std::array`）

> **知识点**：原生数组（`int[]`）不支持 `=` 赋值运算符，`c = d` 编译错误。`std::array` 重载了拷贝赋值运算符，`a = b`（相同类型和大小）合法。原生数组与 `std::array` 之间没有隐式赋值转换。

## 解析

正确答案是 C，即 `a = b;`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
