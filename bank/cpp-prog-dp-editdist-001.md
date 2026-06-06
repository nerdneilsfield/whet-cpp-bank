---
qid: cpp-prog-dp-editdist-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-dp-editdist-001/
---
求两字符串的 Levenshtein 编辑距离（插入/删除/替换各代价 1）。

```cpp
#include <string>
int minDistance(const std::string& a, const std::string& b);
```

## Explanation

令 `dp[i][j]` 表示 `a` 前 i 个字符到 `b` 前 j 个字符的最小编辑距离，首行首列分别初始化为插入或删除次数。若末字符相同继承 `dp[i-1][j-1]`，否则取插入、删除、替换三者最小值加一。注意空字符串边界，空间可优化为两行但转移含义不能变。
