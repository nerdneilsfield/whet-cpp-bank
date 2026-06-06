---
qid: cpp-algo-multi-deep-005
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: [A, B, D]
---

关于二分搜索族（`lower_bound` / `upper_bound` / `equal_range` / `binary_search`），下列哪些**正确**？（多选）

A. 都要求输入序列对**同一比较器**已排序，否则结果未定义
B. `binary_search` 仅返回 `bool`；`lower_bound` 返回插入位置迭代器
C. 在 `std::list` 上能保证 O(log n) 的总时间复杂度
D. 在自定义比较器排序的容器上做二分时，必须传相同的比较器

---

**解析：**

- A ✅：前提是"对该比较器有序"或更弱的"对该谓词分区"。
- B ✅：`binary_search` 不返回位置信息；要位置用 `lower_bound`/`equal_range`。
- C ❌：`std::list` 是 BidirectionalIterator，二分**比较次数** O(log n)，但**移动次数** O(n)，总时间 O(n)。
- D ✅：传入与排序不一致的比较器会破坏二分前提，行为未定义。

常见陷阱：用 `std::sort(v.begin(), v.end(), std::greater<>{})` 后调 `lower_bound` 不传比较器，结果错误。
