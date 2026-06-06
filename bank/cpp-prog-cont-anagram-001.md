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

## 解析
字母异位词可以用排序后的字符串作为 key：同组单词排序后相同。遍历输入时把原字符串追加到对应 key 的 vector 中，因此组内顺序自然保持输入顺序。组间顺序题目不限，可以直接遍历哈希表输出；若测试要求稳定顺序，则额外记录 key 首次出现顺序。
