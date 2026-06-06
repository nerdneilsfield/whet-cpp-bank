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