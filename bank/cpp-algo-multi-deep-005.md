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

## 解析

正确选项是 A、B、D。二分搜索族的前提是范围按同一个比较器有序或分区，比较器不一致会破坏结果。binary_search 只返回 bool，lower_bound 返回插入位置。list 上比较次数可为 O(log n)，但迭代器移动总成本仍是 O(n)。
