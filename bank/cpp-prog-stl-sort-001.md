---
qid: cpp-prog-stl-sort-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-sort-001/
---
给定若干区间 [start, end]，合并所有重叠区间，返回结果按 start 升序排列。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <utility>

std::vector<std::pair<int,int>> merge_intervals(std::vector<std::pair<int,int>> intervals);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数