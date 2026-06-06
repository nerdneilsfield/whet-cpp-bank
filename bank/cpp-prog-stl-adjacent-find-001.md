---
qid: cpp-prog-stl-adjacent-find-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-adjacent-find-001/
---
给定整数数组 `nums`，返回第一对相邻相等元素中前者的下标；不存在则返回 -1。要求使用 `std::adjacent_find`。

约束：0 <= nums.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int first_adjacent_dup(const std::vector<int>& nums);
```

### 示例
```
[1,2,3,3,4] => 2
[1,2,3,4]   => -1
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

使用 `std::adjacent_find(nums.begin(), nums.end())` 找到第一对相邻相等元素的前一个迭代器。若返回 `end()`，说明不存在，返回 -1；否则用 `std::distance` 或迭代器相减得到下标。注意空数组和单元素数组都不会有相邻重复。
