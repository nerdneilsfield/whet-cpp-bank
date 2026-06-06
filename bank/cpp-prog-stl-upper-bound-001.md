---
qid: cpp-prog-stl-upper-bound-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-upper-bound-001/
---
给定升序排列的非空整数数组 `nums` 和一个整数 `x`，返回 `x` 在数组中出现的次数。要求使用 `std::upper_bound` 和 `std::lower_bound` 以 O(log n) 完成。

约束：1 <= nums.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int count_occurrences(const std::vector<int>& nums, int x);
```

## 示例
```
[1,2,2,2,3], 2 => 3
[1,2,3,4], 5  => 0
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。