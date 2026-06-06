---
qid: cpp-prog-ds-deque-window-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-deque-window-001/
---
用 `std::deque` 在 O(n) 内求滑动窗口最大值：给定数组 `a` 与窗口大小 `k`，返回每个窗口的最大值。

```cpp
#include <vector>
std::vector<int> maxSlidingWindow(const std::vector<int>& a, int k);
```

## Explanation

使用双端队列保存候选最大值的下标，并保持下标对应的值单调递减。遍历每个位置时先弹出过期下标，再从队尾弹出不大于当前值的下标，最后把当前下标入队；窗口形成后队首就是最大值。注意 `k <= 0`、空数组和 `k` 大于数组长度的边界要按题目测试处理。
