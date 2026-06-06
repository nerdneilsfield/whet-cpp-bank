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

## Explanation

维护一个大小最多为 k 的最小堆，堆中保存当前最大的 k 个元素。构造和每次 `add` 都插入新值，若堆大小超过 k 就弹出堆顶最小值；此时堆顶就是第 k 大。注意比较器要用 `greater<int>`，不要维护最大堆，否则堆顶含义会反。
