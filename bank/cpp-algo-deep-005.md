---
qid: cpp-algo-deep-005
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码使用 `std::partition`，关于结果哪项**正确**？

```cpp
std::vector<int> v{5, 2, 8, 1, 9, 3, 7, 4, 6};
auto mid = std::partition(v.begin(), v.end(),
                          [](int x){ return x < 5; });
// 前半部分是 < 5 的元素，后半部分是 ≥ 5 的元素
```

A. 前后两半都保持元素在原序列中的相对顺序
B. 前后两半都**不保证**保持相对顺序；若需要保序应使用 `std::stable_partition`
C. `std::partition` 时间复杂度 O(n log n)，必须排序
D. `mid` 指向的位置一定是中间元素，即 `v.begin() + v.size()/2`

## 解析

正确答案是 B：std::partition 只保证满足谓词的元素在前，不满足的在后，不保证两部分内部的原相对顺序。mid 指向后一组的第一个元素，位置由满足谓词的元素个数决定，不一定在物理中点。需要保序时应使用 std::stable_partition。
