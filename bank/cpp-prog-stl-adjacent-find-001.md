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

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int first_adjacent_dup(const std::vector<int>& nums);
```

## 示例
```
[1,2,3,3,4] => 2
[1,2,3,4]   => -1
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。