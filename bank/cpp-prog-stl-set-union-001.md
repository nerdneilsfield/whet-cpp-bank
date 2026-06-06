---
qid: cpp-prog-stl-set-union-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-set-union-001/
---
给定两个升序排列的整数 vector `a` 和 `b`，返回它们的并集（按升序排列，重复元素只保留一次，但若某元素在其中一个数组中多次出现则保留出现次数最大值）。实际上 `std::set_union` 保留最大出现次数。

约束：0 <= a.size(), b.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> set_union(const std::vector<int>& a, const std::vector<int>& b);
```

### 示例
```
[1,2,3], [2,3,4] => [1,2,3,4]
[1,1,2], [1,3]   => [1,1,2,3]
```

### 提示
- 注意函数名 `set_union` 不要与关键字冲突；在 skeleton/solution.hpp 中实现。

## Explanation

使用 `std::set_union` 合并两个升序区间到结果中。多重集合语义下，某元素出现次数取两边次数的较大值，而不是简单去重到一次。注意函数名若与标准算法同名，应通过命名空间或局部调用避免歧义。
