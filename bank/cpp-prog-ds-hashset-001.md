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

## Explanation

用滑动窗口维护当前无重复字符区间，右端扩展时若字符已存在，就移动左端并从集合删除直到冲突消失。每个字符最多进出集合一次，因此总复杂度 O(n)。注意更新答案的位置应在插入当前字符之后，空串结果为 0。
