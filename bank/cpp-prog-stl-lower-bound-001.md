---
qid: cpp-prog-stl-lower-bound-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-lower-bound-001/
---
给定升序排列的整数 vector `sorted` 和一个整数 `x`，将 `x` 插入到合适位置使序列仍然升序（相等元素插入到最左侧），返回新 vector。要求使用 `std::lower_bound`。

约束：0 <= sorted.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> insert_sorted(std::vector<int> sorted, int x);
```

### 示例
```
[1,3,5,7], 4 => [1,3,4,5,7]
[1,2,2,3], 2 => [1,2,2,2,3]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

对升序 vector 调用 `std::lower_bound` 找到第一个不小于 x 的位置，再在该位置插入 x。这样相等元素会插到最左侧，且插入后仍保持升序。注意函数参数按值传入 sorted，可以直接修改并返回，不会影响调用者原数组。
