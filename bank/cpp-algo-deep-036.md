---
qid: cpp-algo-deep-036
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码使用堆算法，正确的"插入"操作是？

```cpp
std::vector<int> v{5,3,8,1,2};
std::make_heap(v.begin(), v.end());  // 默认 max-heap
v.push_back(10);
???
```

A. `std::make_heap(v.begin(), v.end());` 重建堆
B. `std::push_heap(v.begin(), v.end());` 仅 O(log n) 上浮新元素
C. `std::sort_heap(v.begin(), v.end());`
D. `std::pop_heap(v.begin(), v.end());`

## Explanation

正确答案是 B：push_back 新元素后，原来的 [begin,end-1) 已是堆，std::push_heap 只需把新尾元素上浮，复杂度 O(log n)。重新 make_heap 虽正确但多做 O(n) 工作。sort_heap 会把堆排序，pop_heap 是弹出堆顶的准备动作，都不是插入。
