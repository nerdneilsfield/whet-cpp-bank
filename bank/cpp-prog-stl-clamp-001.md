---
qid: cpp-prog-stl-clamp-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-clamp-001/
---
给定整数数组 `nums` 与两个整数 `lo <= hi`，返回一个新数组，其中每个元素被截断到区间 `[lo, hi]`（小于 `lo` 改成 `lo`，大于 `hi` 改成 `hi`，其余保持不变）。要求使用 `std::transform` + `std::clamp`。

约束：0 <= nums.size() <= 10^5；lo <= hi。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> clamp_all(const std::vector<int>& nums, int lo, int hi);
```

## 示例
```
[1,5,8,12,-3], lo=0, hi=10 => [1,5,8,10,0]
[],            lo=0, hi=1  => []
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。