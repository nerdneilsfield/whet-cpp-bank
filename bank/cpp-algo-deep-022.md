---
qid: cpp-algo-deep-022
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码用 `std::partial_sort` 取前 3 小并升序排列，运行后 `v` 是？

```cpp
std::vector<int> v{5,2,8,1,9,3,7,4,6};
std::partial_sort(v.begin(), v.begin()+3, v.end());
// 输出 v
```

A. `1 2 3 4 5 6 7 8 9`
B. `1 2 3` 在前，之后元素**顺序未指定**
C. `1 2 3 5 8 9 7 4 6`（保持原相对顺序）
D. 仅 v[2] 是第 3 小，其他不变

---

**解析：**

`std::partial_sort(first, middle, last)` 保证：

- `[first, middle)` 是整个 `[first, last)` 中**最小的 `middle - first` 个**元素，且**已升序排列**
- `[middle, last)` 中元素**顺序未指定**

复杂度 O(n log k)，k = middle − first。当 k ≪ n 时显著快于 `std::sort` 的 O(n log n)。常用于"取前 K 名"。

若只想求**第 k 小**而不要前 k 个有序，用 `nth_element`，平均 O(n) 更快。
