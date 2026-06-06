---
qid: cpp-prog-stl-binsearch-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-binsearch-001/
---
给定数组 nums，nums[i] != nums[i+1]，找出任意一个峰值元素的下标（峰值：严格大于相邻元素）。要求 O(log n)。两端可视为 -∞。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int find_peak(const std::vector<int>& nums);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
利用相邻元素不相等和两端视为负无穷，可以二分判断斜率方向。若 `nums[mid] < nums[mid+1]`，右侧一定存在峰值；否则左侧含 `mid` 一定存在峰值。循环到 `l == r` 时该位置就是一个峰值，单元素数组也自然成立。
