---
qid: cpp-prog-stl-partial-sum-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-partial-sum-001/
---
给定整数数组 `nums`，返回其前缀和数组 `pref`，其中 `pref[i] = nums[0]+...+nums[i]`。要求使用 `std::partial_sum`。

约束：0 <= nums.size() <= 10^5。结果元素可能较大，使用 `long long`。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<long long> prefix_sum(const std::vector<int>& nums);
```

## 示例
```
[1,2,3,4] => [1,3,6,10]
[]        => []
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。