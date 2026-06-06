---
qid: cpp-prog-str-longestcommon-001
type: prog
kp: [cpp-stl-basics]
primary_kp: cpp-stl-basics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-str-longestcommon-001/
---
求字符串数组的最长公共前缀。空数组返回 `""`。

```cpp
#include <string>
#include <vector>
std::string longestCommonPrefix(const std::vector<std::string>& strs);
```

## Explanation

可以先把第一个字符串作为候选前缀，再逐个字符串缩短候选直到它成为当前字符串的前缀。空数组直接返回空串，若某次候选变空也可提前结束。注意比较时不要越界，公共前缀长度最多是当前字符串和候选长度的较小值。
