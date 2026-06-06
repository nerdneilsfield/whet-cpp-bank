---
qid: cpp-algo-deep-019
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

要在 `v` 中找出**第 k 小的元素**（k=3），并不要求其他元素有序，复杂度最优的算法是？

```cpp
std::vector<int> v{5,2,8,1,9,3,7,4,6};
int k = 3;
???
```

A. `std::sort(v.begin(), v.end()); int kth = v[k-1];` — O(n log n)
B. `std::nth_element(v.begin(), v.begin()+k-1, v.end()); int kth = v[k-1];` — 平均 O(n)
C. `std::partial_sort(v.begin(), v.begin()+k, v.end()); int kth = v[k-1];` — O(n log k)
D. `std::priority_queue<int> pq(v.begin(), v.end()); for(int i=1;i<k;i++) pq.pop(); int kth = pq.top();` — O(n + k log n)

---

**解析：**

`std::nth_element(first, nth, last)` 利用 introselect（基于 quickselect），**平均 O(n)**，将第 n 小元素放到位置 `nth`，使 `[first, nth)` 中元素都 ≤ `*nth`，`[nth+1, last)` 都 ≥ `*nth`，**但两侧内部不排序**。

A 是 O(n log n)，明显劣；C 是 O(n log k)，当 k 很大时差；D 同样 O(n + k log n) 在大 k 下不如 nth_element。

注意：`nth_element` 改变原序列；若只想"前 k 个最小"且需要它们有序，用 `partial_sort`。
