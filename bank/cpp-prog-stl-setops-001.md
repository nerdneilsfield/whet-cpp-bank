---
qid: cpp-prog-stl-setops-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-setops-001/
---
给定两个已升序排列的数组 a 和 b，返回交集（保留重复，按非降序）。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> sorted_intersection(const std::vector<int>& a, const std::vector<int>& b);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数