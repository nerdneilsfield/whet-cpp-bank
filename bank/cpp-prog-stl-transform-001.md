---
qid: cpp-prog-stl-transform-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-transform-001/
---
给定等长向量 a, b，返回元素和向量 c[i] = a[i] + b[i]。要求使用 std::transform。长度不同抛 std::invalid_argument。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> elem_add(const std::vector<int>& a, const std::vector<int>& b);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数