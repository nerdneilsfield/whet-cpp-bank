---
qid: cpp-prog-ds-priority-queue-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-priority-queue-001/
---
实现 `KthLargest`：构造时给定 `k` 与初始数组，`add(val)` 加入并返回当前第 k 大元素。内部用大小不超过 k 的最小堆 (`priority_queue<int, vector<int>, greater<int>>`)。

```cpp
class KthLargest {
public:
    KthLargest(int k, const std::vector<int>& nums);
    int add(int val);
};
```