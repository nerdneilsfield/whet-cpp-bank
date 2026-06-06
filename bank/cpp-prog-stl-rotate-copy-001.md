---
qid: cpp-prog-stl-rotate-copy-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-rotate-copy-001/
---
给定整数数组 `nums` 和非负整数 `k`，将数组循环右移 `k` 步，返回新数组。要求使用 `std::rotate_copy` 完成。`k` 可能大于数组长度，需先取模。

约束：0 <= nums.size() <= 10^5；0 <= k <= 10^9。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> rotate_right(std::vector<int> nums, int k);
```

### 示例
```
[1,2,3,4,5], 2 => [4,5,1,2,3]
[], 3          => []
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

右移 k 位等价于把分割点设为 `end - (k % n)`，再用 `std::rotate_copy` 复制到新 vector。空数组要先特判，避免对 0 取模。注意 `rotate_copy` 不修改原数组，返回的是旋转后的新结果。
