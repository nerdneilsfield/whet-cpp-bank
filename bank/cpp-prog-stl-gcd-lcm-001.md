---
qid: cpp-prog-stl-gcd-lcm-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-gcd-lcm-001/
---
给定非空正整数数组 `nums`，返回所有元素的最大公约数（GCD）。要求结合 `std::gcd`（`<numeric>`）与 `std::accumulate` 或 `std::reduce` 完成。

约束：1 <= nums.size() <= 10^5；1 <= nums[i] <= 10^9。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int gcd_all(const std::vector<int>& nums);
```

## 示例
```
[12,18,24] => 6
[7]        => 7
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。