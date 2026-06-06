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
