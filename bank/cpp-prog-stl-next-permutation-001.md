---
qid: cpp-prog-stl-next-permutation-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-next-permutation-001/
---
给定整数数组 `nums`，原地修改为下一个字典序排列（如果已是最大排列则变成最小排列）。返回是否存在更大的下一个排列。要求使用 `std::next_permutation`。

约束：0 <= nums.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

bool next_perm(std::vector<int>& nums);
```

### 示例
```
[1,2,3]   => 修改为 [1,3,2]，返回 true
[3,2,1]   => 修改为 [1,2,3]，返回 false
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

直接调用 `std::next_permutation(nums.begin(), nums.end())`，它会原地改成下一个字典序排列并返回是否存在更大排列。若当前已是最大排列，算法会重排为最小排列并返回 false。注意空数组或单元素数组也会返回 false，且内容保持为最小排列形式。
