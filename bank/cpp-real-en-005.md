---
qid: cpp-real-en-005
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: easy
answer_key: B
tags: [interview-real, interviewbit]
---
`std::map` 和 `std::unordered_map` 分别应该在什么场景下使用？

A. 总是使用 `std::map`，因为它的查找性能更优
B. 需要有序遍历时用 `std::map`（红黑树 O(log n)）；需要平均 O(1) 查找且不关心顺序时用 `std::unordered_map`（哈希表）
C. `std::unordered_map` 在所有场景下都优于 `std::map`
D. `std::map` 使用哈希表实现，`std::unordered_map` 使用红黑树实现

---

**解析：**

- **`std::map`**：底层是红黑树，元素按键有序存储。插入/查找/删除均为 O(log n)。适用于需要有序遍历、范围查询（`lower_bound` / `upper_bound`）、或键类型没有哈希函数的场景。
- **`std::unordered_map`**：底层是哈希表，平均 O(1) 查找，最坏 O(n)。适用于性能敏感、不需要顺序、且键类型有良好哈希函数的场景。

选择原则：需要顺序 → `map`；追求极速查找不关心顺序 → `unordered_map`。

**来源：** InterviewBit "C++ Interview Questions" — map vs unordered_map

## Explanation

正确答案是 B。
std::map：底层是红黑树，元素按键有序存储；插入/查找/删除均为 O(log n)。
适用于需要有序遍历、范围查询（lower_bound / upper_bound）、或键类型没有哈希函数的场景；std::unordered_map：底层是哈希表，平均 O(1) 查找，最坏 O(n)。
