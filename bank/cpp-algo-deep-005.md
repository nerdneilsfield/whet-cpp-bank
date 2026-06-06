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

---

**解析：**

`std::partition` 是**非稳定**划分，平均复杂度 O(n)，不保证两半内元素的相对顺序。若需要稳定划分，使用 `std::stable_partition`（复杂度 O(n log n) 或在足够内存下 O(n)）。

`mid` 指向**第二组（不满足谓词）的第一个元素**，其位置取决于谓词为真的元素个数，并非固定的中点。`std::partition` 不排序。
