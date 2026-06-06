---
qid: cpp-algo-fill-med-001
type: fill
kp: [cpp-algorithms]
difficulty: medium
answer_key: "binary_search"
---
已排序区间二分查找返回 bool 的算法 `std::___`。

---

**解析：**

`std::binary_search` 对已排序区间执行二分查找，返回 `true`（找到）或 `false`（未找到）。与 `std::lower_bound`（返回迭代器）和 `std::equal_range`（返回一对迭代器）不同，`binary_search` 只关心存在性。其复杂度为 O(log n)，要求输入区间必须已按比较函数排序。