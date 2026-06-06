---
qid: cpp-prog-cont-twosum-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-cont-twosum-001/
---
给定 nums 和 target，返回两个使其和为 target 的下标（任一解，i<j）。无解返回 {-1,-1}。使用 unordered_map 实现 O(n)。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <utility>

std::pair<int,int> two_sum(const std::vector<int>& nums, int target);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数