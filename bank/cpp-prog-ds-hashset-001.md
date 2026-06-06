---
qid: cpp-prog-ds-hashset-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-ds-hashset-001/
---
滑动窗口 + `unordered_set`，求最长无重复字符子串长度。

```cpp
#include <string>
int lengthOfLongestSubstring(const std::string& s);
```