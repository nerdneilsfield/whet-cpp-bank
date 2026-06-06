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

## Explanation

正确答案是 C：equal_range 返回 pair<lower_bound, upper_bound>，正好表示所有等于 3 的半开区间。binary_search 只给 bool，lower_bound 只有左边界，find 又是线性查找。前提是序列已按同一比较器排序。
