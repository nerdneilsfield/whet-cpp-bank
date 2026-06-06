---
qid: cpp-prog-stl-nth-element-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-nth-element-001/
---
给定非空整数数组 nums，返回中位数（向下取整位置 `n/2`）。要求使用 `std::nth_element` 以 O(n) 期望复杂度完成。

约束：1 <= nums.size() <= 10^5。中位数定义为排序后下标 `nums.size()/2` 的元素。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int find_median(std::vector<int> nums);
```

## 示例
```
[3,1,2,4,5] => 3 (排序后[1,2,3,4,5]，下标 2)
[1,2]       => 2 (排序后[1,2]，下标 1)
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。