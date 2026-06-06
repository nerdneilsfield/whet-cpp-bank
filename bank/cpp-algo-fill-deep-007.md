---
qid: cpp-algo-fill-deep-007
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["O(log n)", "logarithmic", "对数"]
---

`std::set<int>` 的成员函数 `find(key)` 的时间复杂度是 _______（请以大 O 记号给出）。

---

**解析：**

`std::set` / `std::map` 基于**自平衡红黑树**实现，`find` / `insert` / `erase` 均为 **O(log n)**。

对比：
- `std::unordered_set::find` → 平均 O(1)，最坏 O(n)（哈希冲突）
- `std::find(s.begin(), s.end(), key)`（通用算法）→ **O(n)**：通用算法只看迭代器类别，不利用容器结构

教训：在有序/哈希容器上，优先调用**成员 find**，速度差 1~2 个数量级。同理 `count` / `lower_bound` / `upper_bound` / `equal_range` 都有 set/map 的成员版本。

C++20 起还有 `contains(key)`：`if (s.contains(key)) {...}` 比 `s.find(key) != s.end()` 简洁。
