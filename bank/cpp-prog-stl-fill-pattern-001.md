---
qid: cpp-prog-stl-fill-pattern-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-stl-fill-pattern-001/
---
给定非负整数 `n` 和单个整数 `value`，返回一个长度为 `n`、所有元素都等于 `value` 的 vector。要求使用 `std::fill_n`。

约束：0 <= n <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>

std::vector<int> make_filled(int n, int value);
```

## 示例
```
n=4, value=7 => [7,7,7,7]
n=0, value=9 => []
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。