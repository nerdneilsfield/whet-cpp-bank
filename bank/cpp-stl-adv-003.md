---
qid: cpp-stl-adv-003
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# arr.at(i) vs arr[i] 越界行为

```cpp
#include <array>
#include <stdexcept>

std::array<int, 3> arr = {10, 20, 30};
```

访问 `arr[5]` 和 `arr.at(5)` 时，下面哪个描述最准确？

A. 两者都抛出 `std::out_of_range` 异常
B. `arr[5]` 是未定义行为（UB），`arr.at(5)` 抛出 `std::out_of_range` 异常
C. `arr[5]` 返回默认值 0，`arr.at(5)` 抛出异常
D. 两者都是未定义行为，区别仅在于性能

> **知识点**：`operator[]` 不做越界检查，访问越界是未定义行为（可能读脏数据、崩溃或任何事）。`at()` 先检查下标范围，越界时抛 `std::out_of_range`，是安全但略慢的访问方式。

## Explanation

正确答案是 B，即 `arr[5]` 是未定义行为（UB），`arr.at(5)` 抛出 `std::out_of_range` 异常。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
