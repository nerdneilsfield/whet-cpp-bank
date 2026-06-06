---
qid: cpp-stl-multi-med-002
type: multi
kp: [cpp-stl-basics]
difficulty: medium
answer_key: [A, B, D]
---
关于迭代器失效规则，**哪些说法是正确的**？（多选）

A. `vector::push_back` 在容量重新分配时使所有迭代器失效。
B. `list` 的插入只影响新插入节点附近，不会使其它迭代器失效。
C. `map::erase` 后，返回的迭代器以外的所有迭代器都会失效。
D. `unordered_map::insert` 在触发 rehash 时使所有迭代器失效，但不影响节点本身的引用。

---

**解析：**

A 正确：容量增长导致重新分配，全部迭代器与引用失效。
B 正确：链表稳定，其它迭代器不受影响。
C 错误：`map::erase` 只让被删除元素的迭代器失效，其它迭代器仍有效。
D 正确：rehash 后桶结构变化，迭代器失效；但节点内存稳定，引用不失效（直到节点被删除）。