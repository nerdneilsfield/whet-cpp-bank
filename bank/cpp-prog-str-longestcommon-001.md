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