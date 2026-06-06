---
qid: cpp-prog-stl-set-intersection-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-set-intersection-001/
---
给定两个升序排列的整数 vector `a` 和 `b`，返回它们的交集（升序排列，每个公共元素出现的次数取其在两数组中出现次数的较小值）。要求使用 `std::set_intersection`。

约束：0 <= a.size(), b.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> set_intersect(const std::vector<int>& a, const std::vector<int>& b);
```

### 示例
```
[1,2,3], [2,3,4] => [2,3]
[1,1,2,3], [1,1,1,2] => [1,1,2]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

使用 `std::set_intersection` 求两个升序区间的交集，并写入结果 vector。重复元素的保留次数是两边出现次数的较小值。注意这不是哈希集合交集，不能丢掉重复计数。
