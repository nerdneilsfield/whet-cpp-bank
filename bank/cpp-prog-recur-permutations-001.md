---
qid: cpp-prog-recur-permutations-001
type: prog
kp: [cpp-functions]
primary_kp: cpp-functions
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-recur-permutations-001/
---
返回 distinct 整数数组的全排列。结果集顺序不限，测试将排序后比较。

```cpp
#include <vector>
std::vector<std::vector<int>> permute(std::vector<int> nums);
```