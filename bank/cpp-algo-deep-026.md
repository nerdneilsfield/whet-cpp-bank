---
qid: cpp-algo-deep-026
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码在已排序向量中查找 `3` 的**插入位置范围**，正确算法是？

```cpp
std::vector<int> v{1,2,3,3,3,4,5};
???
// 期望 [first, last) 是所有等于 3 的元素区间
```

A. `auto p = std::binary_search(v.begin(), v.end(), 3);`
B. `auto p = std::lower_bound(v.begin(), v.end(), 3);`
C. `auto p = std::equal_range(v.begin(), v.end(), 3);` 返回 `pair<iter, iter>`
D. `auto p = std::find(v.begin(), v.end(), 3);` — O(log n)

---

**解析：**

- `lower_bound`：返回**不小于** value 的第一个位置（值 3 的左边界，可插入处）
- `upper_bound`：返回**严格大于** value 的第一个位置（值 3 的右边界后）
- `equal_range`：返回 `pair{lower_bound, upper_bound}`，即等于 value 的整个连续区间
- `binary_search`：只返回 `bool`，不告知位置

`std::equal_range` 一次完成两件事，比分别调 lower/upper 略快（共享路径）。`std::find` 是 O(n)。在 `std::multiset` 上也常用 `equal_range` 取所有等值元素。
