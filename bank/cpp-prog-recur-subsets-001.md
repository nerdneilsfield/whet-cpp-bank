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

## Explanation

回溯时对每个元素做“选”或“不选”两种决策，走到末尾时记录当前子集。也可以从当前位置开始逐个加入元素生成所有前缀扩展。注意每次递归返回要弹出刚加入的元素，空集也必须包含在结果中。
