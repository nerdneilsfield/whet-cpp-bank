---
qid: cpp-prog-stl-count-if-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-count-if-001/
---
给定整数数组 `nums`，返回其中偶数的个数（0 算偶数；负数按通常奇偶定义）。要求使用 `std::count_if` + lambda。

约束：0 <= nums.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int count_even(const std::vector<int>& nums);
```

## 示例
```
[1,2,3,4,5,6] => 3
[1,3,5]       => 0
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。