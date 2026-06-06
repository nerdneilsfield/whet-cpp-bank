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

## 解析

正确答案是 B：partial_sort 保证前 k 个位置放置全局最小的 k 个元素，并且这 k 个元素内部已经排序。middle 之后的元素仍然存在，但顺序未指定，也不保证保持原相对顺序。误区是把 partial_sort 当成完整 sort，期待整个 vector 都有序。
