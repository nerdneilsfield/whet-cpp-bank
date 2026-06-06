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

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>

bool is_anagram(const std::string& a, const std::string& b);
```

### 示例
```
"listen", "silent" => true
"abc", "abd"       => false
```

### 提示
- 在 skeleton/solution.hpp 中实现函数。

## Explanation

先比较长度，不同长度不可能互为排列；长度相同再调用 `std::is_permutation(a.begin(), a.end(), b.begin())`。该算法按元素出现次数判断，而不是只判断集合相同。注意长字符串上它可能不是最优复杂度，但本题要求使用该 STL 算法。
