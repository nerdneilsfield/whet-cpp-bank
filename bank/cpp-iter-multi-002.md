---
qid: cpp-iter-multi-002
type: multi
kp: [cpp-iterators]
difficulty: medium
answer_key: [A, B, D]
---
关于迭代器失效的原因，**哪些说法是正确的**？（多选）

A. `vector::push_back` 触发容量增长时，所有原迭代器失效。
B. `unordered_map` 在 rehash（如 `insert` 触发负载因子超限）时，所有迭代器失效。
C. `list::splice` 操作总是使所有迭代器失效。
D. 删除关联容器中的某个元素，只会让指向该元素的迭代器失效，其它迭代器仍有效。

---

**解析：**

A 正确：容量增长导致重新分配。
B 正确：rehash 使迭代器失效（但节点稳定，引用/指针仍有效）。
C 错误：`list::splice` 不使迭代器失效，元素从一个 list 移到另一个 list，迭代器依然有效。
D 正确：`map`、`set` 等关联容器中 erase 只影响被删除元素的迭代器。