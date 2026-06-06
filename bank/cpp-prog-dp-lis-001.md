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

## Explanation

维护数组 `tails`，其中 `tails[len-1]` 是长度为 len 的严格递增子序列可能的最小尾值。遍历元素时用 `lower_bound` 找到第一个不小于它的位置并替换，若在末尾则扩展长度。严格递增必须用 `lower_bound`，若误用 `upper_bound` 会把相等元素也计入长度。
