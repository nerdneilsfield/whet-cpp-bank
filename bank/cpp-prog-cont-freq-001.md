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

## 解析
创建 `unordered_map<char,int>`，遍历字符串并对每个字符执行 `++freq[c]` 即可，默认构造的 int 计数会从 0 开始。空字符串不进入循环，直接返回空 map。不要假设字符只包含字母，按 `char` 原值统计才能覆盖标点、空格、数字等输入。
