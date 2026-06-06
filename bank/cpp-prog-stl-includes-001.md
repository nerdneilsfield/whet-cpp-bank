---
qid: cpp-prog-stl-includes-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-includes-001/
---
给定两个升序排列的整数 vector `a` 和 `b`，判断 `a` 是否包含 `b` 中的全部元素（按多重集合语义，即每个元素的出现次数 `a` 中都不少于 `b`）。要求使用 `std::includes`。

约束：0 <= a.size(), b.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

bool contains_all(const std::vector<int>& a, const std::vector<int>& b);
```

## 示例
```
a=[1,2,2,3,4], b=[2,2,4]  => true
a=[1,2,3],     b=[2,4]    => false
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。