---
qid: cpp-prog-stl-find-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-find-001/
---
给定整数数组 nums 和正整数 k，返回出现频率前 k 高的元素，按频率降序排列。频率相同则按数值升序。

约束：1 <= nums.size() <= 10^5，1 <= k <= 不同元素数。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> top_k_frequent(const std::vector<int>& nums, int k);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数