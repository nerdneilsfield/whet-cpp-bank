---
qid: cpp-prog-stl-find-if-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-find-if-001/
---
给定整数数组 `nums`，返回第一个负数元素的下标；不存在则返回 -1。要求使用 `std::find_if`。

约束：0 <= nums.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int first_negative_index(const std::vector<int>& nums);
```

## 示例
```
[3,5,-1,7,-2] => 2
[1,2,3]       => -1
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。