---
qid: cpp-prog-stl-equal-range-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-equal-range-001/
---
给定升序排列的整数数组 `nums` 和一个值 `x`，返回所有等于 `x` 的元素组成的 vector（保持原顺序，可能为空）。要求使用 `std::equal_range`。

约束：0 <= nums.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> find_all_equal(const std::vector<int>& nums, int x);
```

## 示例
```
[1,2,2,2,3], 2 => [2,2,2]
[1,2,3], 5     => []
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。