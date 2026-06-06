---
qid: cpp-prog-stl-is-permutation-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-is-permutation-001/
---
给定两个字符串 `a` 和 `b`，判断它们是否为字母异位词（即互为排列，字符种类与各自出现次数完全相同）。要求使用 `std::is_permutation`。

约束：0 <= a.size(), b.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>

bool is_anagram(const std::string& a, const std::string& b);
```

## 示例
```
"listen", "silent" => true
"abc", "abd"       => false
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。