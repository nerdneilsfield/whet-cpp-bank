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

## 解析

正确答案是 B：std::nth_element 能把第 k 小元素放到目标位置，平均线性时间，且不要求两侧内部有序。sort 做了过多工作，partial_sort 适合前 k 个有序但复杂度更高。若只关心第 k 小，nth_element 是最匹配的算法。
