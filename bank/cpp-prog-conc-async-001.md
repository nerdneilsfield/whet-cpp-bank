---
qid: cpp-prog-conc-async-001
type: prog
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-conc-async-001/
---
实现 parallel_sum(v, lo, hi) 使用 std::async 分半计算并行求和。当范围小于 1000 时直接串行累加。

## 函数签名
```cpp
#pragma once
#include <vector>
#include <future>

long long parallel_sum(const std::vector<int>& v, std::size_t lo, std::size_t hi);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数