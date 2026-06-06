---
qid: cpp-prog-cont-freq-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-cont-freq-001/
---
统计字符串中每个字符的出现次数，返回 unordered_map<char,int>。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>
#include <unordered_map>

std::unordered_map<char,int> char_freq(const std::string& s);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数