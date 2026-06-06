---
qid: cpp-prog-stl-iota-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-iota-001/
---
给定正整数 `n`，返回一个长度为 `n` 的 vector，包含 `1, 2, ..., n` 的升序序列。要求使用 `std::iota`。

约束：1 <= n <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> sequence(int n);
```

### 示例
```
5 => [1,2,3,4,5]
1 => [1]
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

创建长度为 n 的 vector，然后调用 `std::iota(result.begin(), result.end(), 1)` 填入递增序列。`iota` 会从初值开始逐个自增写入。注意 n 至少为 1，但实现对 n 为 0 也可自然返回空数组。
