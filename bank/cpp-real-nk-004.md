---
qid: cpp-real-nk-004
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: medium
answer_key: C
tags: [interview-real, nowcoder]
---

在实际场景中，如果需要在**有序数据**上频繁进行**范围查找**（例如找出 `[100, 200]` 之间的所有元素），以下哪种容器最合适？

A. `std::unordered_map<int, int>`
B. `std::map<int, int>`
C. `std::vector<std::pair<int, int>>` 在插入后排序一次 + `std::lower_bound`
D. `std::set<std::pair<int, int>>`

---

**解析：**

这是一个很实际的性能陷阱题：

- **unordered_map**：哈希表无序，无法做范围查找，只能逐个遍历，O(n)
- **map**：红黑树结构，`lower_bound` + 迭代遍历可以找到区间，均摊约为 O(k + log n)（k 是区间长度），但常数大（树节点分散在堆上）
- **vector 排序 + binary search**：连续内存，cache 友好。范围查找用 `lower_bound` 和 `upper_bound` 找边界后线性遍历区间。常数远小于 map
- **set**：会对所有 pair 按字典序排序，语义不对

实测中，对于百万级以下的数据集，sys 时间的差异可以大到 10 倍以上。map 只有在频繁插入/删除 **同时** 需要范围查询的场景下才有优势。

**来源：** 牛客网 C++ STL 高频面试题