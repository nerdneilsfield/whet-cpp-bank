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

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> sorted_intersection(const std::vector<int>& a, const std::vector<int>& b);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
输入已经有序，可以用双指针线性扫描，复杂度为 O(a.size()+b.size())。当两边元素相等时，把该值加入结果并同时前进，这样能按两边出现次数的较小值保留重复元素。若一侧较小，只移动较小的一侧；任一数组耗尽后结束，结果天然保持非降序。
