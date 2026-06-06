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

### 函数签名
```cpp
#pragma once
#include <vector>
#include <future>

long long parallel_sum(const std::vector<int>& v, std::size_t lo, std::size_t hi);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

解题思路是把区间 `[lo, hi)` 按中点拆成两半，一半用 `std::async(std::launch::async, ...)` 递归计算，另一半在当前线程计算后与 future 结果相加。区间长度小于 1000 时直接顺序累加，避免为小任务创建线程的开销。注意边界应使用半开区间，空区间返回 0，递归时不要复制整个 vector。
