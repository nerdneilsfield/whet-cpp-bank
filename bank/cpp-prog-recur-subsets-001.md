---
qid: cpp-prog-recur-subsets-001
type: prog
kp: [cpp-functions]
primary_kp: cpp-functions
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-recur-subsets-001/
---
返回数组的所有子集（幂集）。输入元素互不相同。子集集合内顺序、内部顺序均不要求，测试会排序后比较。

```cpp
#include <vector>
std::vector<std::vector<int>> subsets(const std::vector<int>& nums);
```