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
