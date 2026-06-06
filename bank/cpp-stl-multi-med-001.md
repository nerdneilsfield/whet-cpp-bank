---
qid: cpp-stl-multi-med-001
type: multi
kp: [cpp-stl-basics]
difficulty: medium
answer_key: [A, B, C]
---
关于 `std::vector` 与 `std::list` 的权衡，**哪些说法是正确的**？（多选）

A. `vector` 支持随机访问，`list` 不支持随机访问。
B. `list` 在任意位置插入/删除是 O(1)（已知迭代器），`vector` 通常是 O(n)。
C. `vector` 具有更好的缓存局部性，遍历常常比 `list` 快。
D. `list::size()` 在任意 C++ 标准下都是 O(1)。

---

**解析：**

A 正确：`list` 是双向链表，只能顺序访问。
B 正确：链表插入/删除节点 O(1)，前提是已有迭代器。
C 正确：连续内存的 `vector` 缓存友好。
D 错误：C++11 起 `list::size()` 才被要求是 O(1)；C++03 是实现定义，许多实现是 O(n)。