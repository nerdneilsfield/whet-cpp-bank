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

## Explanation

使用回溯或交换法枚举排列：固定当前位置，递归选择剩余每个元素，达到末尾时把当前排列加入答案。输入元素 distinct，因此不需要额外去重。注意递归返回时要撤销选择或交换回来，避免影响其他分支。
