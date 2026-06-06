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

---

**解析：**

堆算法 4 件套（最大堆，默认 `std::less`）：

- `make_heap`：把整个区间建堆，O(n)
- `push_heap`：要求 `[first, last-1)` 已是堆，且 `*(last-1)` 是新插入元素，上浮调整，O(log n)
- `pop_heap`：把堆顶（`*first`，最大值）和 `*(last-1)` 交换，然后对 `[first, last-1)` 下沉重新成堆，**不真正删除**，需自己 `v.pop_back()`，O(log n)
- `sort_heap`：反复 pop_heap 把堆变排序数组，O(n log n)

`std::priority_queue<T>` 默认用 `vector<T>` + `std::less<T>` 构成 **max-heap**，与上述算法一致；想要 min-heap 传 `std::greater<T>`。
