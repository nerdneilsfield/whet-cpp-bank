---
qid: cpp-prog-stl-copy-if-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-copy-if-001/
---
给定整数数组 `nums`，返回仅包含正数（>0）的新 vector，保持原顺序。要求使用 `std::copy_if`。

约束：0 <= nums.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> filter_positive(const std::vector<int>& nums);
```

## 示例
```
[-2,3,0,5,-1,8] => [3,5,8]
[]              => []
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。