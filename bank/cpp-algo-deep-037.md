---
qid: cpp-algo-deep-037
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列代码 `std::priority_queue<int>` 默认是 max-heap，要改成 min-heap 应该传？

```cpp
std::priority_queue<int, std::vector<int>, ???> pq;
```

A. `std::less<int>`
B. `std::min<int>`
C. `std::greater<int>`
D. `std::not_equal_to<int>`

## Explanation

正确答案是 C：priority_queue 默认 Compare 是 std::less，因此 top 是最大值。改用 std::greater<int> 后，较大的元素被认为优先级更低，最小值会在 top，形成 min-heap。误区是把 sort 中 greater 的降序直觉直接套到 priority_queue 上。
