---
qid: cpp-prog-stl-set-difference-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-set-difference-001/
---
给定两个升序排列的整数 vector `a` 和 `b`，返回属于 `a` 但不属于 `b` 的元素（按升序排列）。多重集合语义：若 `x` 在 `a` 中出现 `m` 次、在 `b` 中出现 `n` 次，则结果中出现 `max(m-n, 0)` 次。要求使用 `std::set_difference`。

约束：0 <= a.size(), b.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> set_diff(const std::vector<int>& a, const std::vector<int>& b);
```

## 示例
```
[1,2,3,4], [2,4] => [1,3]
[1,1,1,2], [1,2] => [1,1]
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。