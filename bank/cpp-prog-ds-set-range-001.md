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