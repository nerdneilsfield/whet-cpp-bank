---
qid: cpp-iter-013
type: multi
kp: [cpp-iterators]
difficulty: easy
answer_key: [A, C, D]
---

对于 `std::vector<int> v = {1, 2, 3, 4, 5};`，以下哪些说法正确？（多选）

A. `*v.rbegin()` 的值是 5
B. `*v.rend()` 的值是 1
C. `v.rbegin()` 对应正向迭代器的 `v.end()` 前一个位置
D. 对反向迭代器 `++` 操作，逻辑上向容器头部移动
E. `v.rend()` 可以被解引用，值为 1
