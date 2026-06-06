---
qid: cpp-algo-fill-deep-002
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::lower_bound", "lower_bound", "std::ranges::lower_bound"]
---

在已升序排好的 `std::vector<int> v` 中，要找到**不小于** `value` 的第一个元素位置（即可插入位置左边界），应使用 STL 算法 _______。

---

**解析：**

`std::lower_bound(first, last, value)`：在已按 `<` 排序的范围内做二分，返回第一个 `>= value` 的迭代器，复杂度 O(log n)（RandomAccess 上）。

相关：
- `std::upper_bound`：第一个 `> value`
- `std::equal_range`：返回 pair{lower, upper}
- `std::binary_search`：仅返回 bool

要传与排序一致的比较器；对 `std::list` 仍可用但移动迭代器开销 O(n)。
