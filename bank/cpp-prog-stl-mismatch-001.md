---
qid: cpp-prog-stl-mismatch-001
type: prog
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-mismatch-001/
---
给定两个字符串 `a` 和 `b`，返回二者第一个不同字符在 `a` 中的下标。若一个是另一个的前缀，返回较短者的长度。若完全相等，返回 `a.size()`。要求使用 `std::mismatch`。

约束：0 <= a.size(), b.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>

int first_mismatch(const std::string& a, const std::string& b);
```

## 示例
```
"hello", "help"   => 3
"abc",   "abc"    => 3
"abc",   "ab"     => 2
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。