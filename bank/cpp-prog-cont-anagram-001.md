---
qid: cpp-prog-cont-anagram-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-cont-anagram-001/
---
给定字符串数组，将字母异位词分组返回。组内顺序保留输入顺序，组间顺序不限。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <vector>
#include <string>

std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& strs);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数