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