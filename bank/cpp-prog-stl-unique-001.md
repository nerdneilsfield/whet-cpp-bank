---
qid: cpp-prog-stl-unique-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-unique-001/
---
移除字符串中相邻重复字符。例如 "aaabccdd" -> "abcd"。空串返回空串。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>

std::string dedup_adjacent(std::string s);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数