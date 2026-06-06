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
