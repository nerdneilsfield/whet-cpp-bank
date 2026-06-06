---
qid: cpp-prog-stl-reduce-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-reduce-001/
---
给定整数数组 `nums`，返回所有元素之和。要求使用 `std::reduce`（`<numeric>`），使用默认执行策略（`std::execution::seq`）。不需要真正并行执行，但需了解 `reduce` API 与 `accumulate` 的区别（结合律不要求一致，但初值类型决定结果类型）。

约束：0 <= nums.size() <= 10^5。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

long long sum_with_reduce(const std::vector<int>& nums);
```

### 示例
```
[1,2,3,4] => 10
[]        => 0
```

### 提示
- 注意初值用 `0LL` 防止溢出；在 skeleton/solution.hpp 中实现。

## Explanation

使用 `std::reduce` 对整个数组归约求和，初值写成 `0LL` 保证累加类型为 `long long`。默认顺序策略即可，不需要显式并行；整数加法满足结合律，reduce 的重排语义不会改变数学结果。注意空数组返回初值 0。
