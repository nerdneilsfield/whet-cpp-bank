---
qid: cpp-algo-multi-deep-007
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B, C]
---

关于 set 系列算法（`set_union` 等），下列哪些**正确**？（多选）

A. 全部要求两输入序列已按**同一比较器**排序
B. 输出序列同样按该比较器有序
C. 时间复杂度 O(m + n)
D. 输入必须是 `std::set` 容器

## 解析

正确选项是 A、B、C。set_union、set_intersection 等算法基于归并，要求两个输入序列按同一比较器排序，输出也按该比较器保持有序。每个输入元素最多被线性扫描一次，所以复杂度是 O(m+n)。它们不要求输入容器是 std::set，名字里的 set 指集合语义。
