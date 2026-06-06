---
qid: cpp-prog-dp-lis-001
type: prog
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-dp-lis-001/
---
求最长严格递增子序列长度，建议 O(n log n)（`lower_bound`）。

```cpp
#include <vector>
int lengthOfLIS(const std::vector<int>& a);
```