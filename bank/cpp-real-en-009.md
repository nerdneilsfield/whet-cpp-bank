---
qid: cpp-real-en-009
type: multi
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: medium
answer_key: ["A", "B", "E"]
tags: [interview-real, interviewbit]
---
关于 C++ 标准序列容器和关联容器的对比，以下哪些说法是正确的？（多选）

A. `std::vector` 在尾部插入/删除快（均摊 O(1)），中间插入/删除慢（O(n)）
B. `std::list` 是双向链表，任意位置插入/删除均为 O(1)（前提是已持有迭代器）
C. `std::deque` 只能在头部和尾部操作，不允许中间插入
D. `std::map` 和 `std::unordered_map` 的所有操作时间复杂度完全相同
E. `std::unordered_map` 的迭代器顺序与插入顺序无关

---

**解析：**

- **`vector`**：连续内存，尾部 O(1)（均摊），中间 O(n) 因为需要移动元素。
- **`list`**：双向链表，已知迭代器位置插入/删除 O(1)，但不支持随机访问。
- **`deque`**：双端队列，头部和尾部插入/删除 O(1)，也支持中间插入（O(n)），支持 `operator[]`。
- **`map`**：红黑树，有序 O(log n)；**`unordered_map`** 哈希表，平均 O(1) 最坏 O(n)；两者时间复杂度不同。
- **`unordered_map`**：迭代器顺序由哈希桶决定，与插入顺序无关。

**来源：** InterviewBit "C++ Interview Questions" — Containers