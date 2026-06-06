---
qid: cpp-prog-stl-inner-product-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-inner-product-001/
---
给定两个等长的整数 vector `a` 和 `b`，计算它们的点积（`sum(a[i]*b[i])`）。要求使用 `std::inner_product`。

约束：0 <= a.size() == b.size() <= 10^5；点积结果在 `long long` 范围内。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

long long dot_product(const std::vector<int>& a, const std::vector<int>& b);
```

### 示例
```
[1,2,3], [4,5,6] => 32   (1*4+2*5+3*6)
[],      []      => 0
```

### 提示
- 注意初值用 `0LL` 避免溢出；在 skeleton/solution.hpp 中实现。

## Explanation

使用 `std::inner_product(a.begin(), a.end(), b.begin(), 0LL)` 计算点积。初值必须是 `0LL`，否则中间结果可能按 int 累加并溢出。题目保证两数组等长，空数组结果自然为 0。
