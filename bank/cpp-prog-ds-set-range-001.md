---
qid: cpp-prog-ds-set-range-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-ds-set-range-001/
---
实现 `RangeCounter`：内部用 `std::set<int>`，支持 `insert(x)` 与 `countInRange(lo, hi)`（闭区间 `[lo, hi]` 内元素个数，使用 `lower_bound/upper_bound`，O(log n + k)）。

```cpp
class RangeCounter {
public:
    void insert(int x);
    int countInRange(int lo, int hi) const;
};
```

## Explanation

内部 `std::set<int>` 自动保持元素有序且去重，`insert` 直接插入即可。查询闭区间时用 `lower_bound(lo)` 找到第一个不小于 lo 的元素，用 `upper_bound(hi)` 找到第一个大于 hi 的元素，再遍历计数。注意 `lo > hi` 时应返回 0，复杂度是 O(log n + k) 而不是纯 O(log n)。
