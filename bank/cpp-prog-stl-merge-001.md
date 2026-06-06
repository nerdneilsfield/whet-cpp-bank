---
qid: cpp-prog-stl-merge-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-merge-001/
---
给定两个升序排列的整数 vector `a` 和 `b`，返回它们合并后的升序 vector（保留所有重复元素）。要求使用 `std::merge`。

约束：0 <= a.size(), b.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b);
```

## 示例
```
[1,3,5], [2,4,6] => [1,2,3,4,5,6]
[1,1,2], [1,3]   => [1,1,1,2,3]
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。