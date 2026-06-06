---
qid: cpp-cont-009
type: multi
kp: [cpp-containers]
difficulty: easy
answer_key: [A, D]
---

对 `std::vector` 执行 `push_back` 触发扩容时，哪些说法正确？（多选）

A. 所有已有迭代器、指针、引用均失效
B. 只有指向末尾元素的迭代器失效
C. `std::map` 执行 `insert` 时也会导致迭代器失效
D. `std::list` 执行 `insert` 时，现有迭代器不失效

## 解析

正确答案是 A、D。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。 A 正确：所有已有迭代器、指针、引用均失效；B 错误：只有指向末尾元素的迭代器失效；C 错误：｀std::map｀ 执行 ｀insert｀ 时也会导致迭代器失效；D 正确：｀std::list｀ 执行 ｀insert｀ 时，现有迭代器不失效。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
