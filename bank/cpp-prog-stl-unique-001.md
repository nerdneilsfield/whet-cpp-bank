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

## 解析
只需要压缩相邻重复字符，不是去掉所有重复字符，因此像 `abca` 中两个 a 都应保留。可以遍历原串，把第一个字符或与结果末尾不同的字符追加到结果中；空串自然返回空结果。若使用 `std::unique`，记得它只把唯一前缀移到前面，还需要 `erase` 删除尾部。
