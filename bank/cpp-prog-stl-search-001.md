---
qid: cpp-prog-stl-search-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-search-001/
---
给定两个整数 vector `hay` 和 `needle`，返回 `needle` 作为子序列在 `hay` 中第一次出现的起始下标；不存在则返回 -1。要求使用 `std::search`。空 `needle` 视为出现在下标 0。

约束：0 <= hay.size(), needle.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

int find_subsequence(const std::vector<int>& hay, const std::vector<int>& needle);
```

### 示例
```
hay=[1,2,3,4,5], needle=[3,4] => 2
hay=[1,2,3],     needle=[4]   => -1
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

调用 `std::search(hay.begin(), hay.end(), needle.begin(), needle.end())` 查找 needle 第一次连续出现的位置。空 needle 按标准会匹配 begin，因此返回 0；未找到则返回 -1。注意这里是连续子序列而不是可以跳元素的子序列。
