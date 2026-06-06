---
qid: cpp-prog-stl-heap-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-heap-001/
---
使用 std::priority_queue 返回数组中最大的 k 个元素，按降序排列。k > size 时返回全部按降序。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> k_largest(const std::vector<int>& nums, int k);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
把所有元素放入默认 `std::priority_queue<int>` 可得到最大堆。弹出 `min(k, nums.size())` 次并依次写入结果，顺序自然是降序。注意 `k <= 0` 时合理返回空结果，`k` 大于数组长度时返回全部元素。
