---
qid: cpp-prog-stl-accumulate-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-accumulate-001/
---
给定 double 数组，使用 std::accumulate 计算均值和样本方差（除以 n，非 n-1）。返回 pair<mean, variance>。空数组返回 {0,0}。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <utility>

std::pair<double,double> mean_var(const std::vector<double>& v);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数