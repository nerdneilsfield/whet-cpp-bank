---
qid: cpp-prog-stl-min-element-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-min-element-001/
---
给定非空整数数组 `nums`，一次遍历返回 `(min, max)` pair。要求使用 `std::minmax_element` 而不是分别调用 `min_element` 和 `max_element`。

约束：1 <= nums.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <utility>

std::pair<int,int> find_min_max(const std::vector<int>& nums);
```

### 示例
```
[3,1,4,1,5,9,2,6] => (1, 9)
[7]               => (7, 7)
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

`std::minmax_element` 一次遍历同时返回最小和最大元素的迭代器，比单独找两次更符合题意。输入非空，因此可以安全解引用返回迭代器并组成 pair。注意若有多个相等最小或最大值，题目只关心值而不是位置。
