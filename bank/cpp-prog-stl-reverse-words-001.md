---
qid: cpp-prog-stl-reverse-words-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-stl-reverse-words-001/
---
给定字符串 `s`，单词之间用单个空格分隔，单词内部不含空格。将单词顺序反转，仍以单个空格连接。允许使用 `std::reverse`、`std::find` 等 STL 算法。前后无多余空格。

约束：0 <= s.size() <= 10^5。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>

std::string reverse_words(const std::string& s);
```

## 示例
```
"hello world foo" => "foo world hello"
"abc"             => "abc"
""                => ""
```

## 提示
- 在 skeleton/solution.hpp 中实现函数。