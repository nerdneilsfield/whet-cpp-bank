---
qid: cpp-prog-stl-partial-sort-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-partial-sort-001/
---
给定整数数组 nums 和正整数 k，返回最小的 k 个元素，按升序排列。要求使用 `std::partial_sort`，复杂度为 O(n log k)。

约束：1 <= k <= nums.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> top_k_smallest(std::vector<int> nums, int k);
```

### 示例
```
nums = [7,2,5,1,3,9,4], k = 3  =>  [1,2,3]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

调用 `std::partial_sort(nums.begin(), nums.begin()+k, nums.end())` 可把最小 k 个元素排好放在前 k 位。再拷贝或截取前 k 个元素作为返回值即可。注意 k 的范围题目保证合法，`partial_sort` 适合 k 远小于 n 的场景。
