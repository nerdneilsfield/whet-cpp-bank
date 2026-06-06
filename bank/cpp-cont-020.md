---
qid: cpp-cont-020
type: multi
kp: [cpp-containers]
difficulty: easy
answer_key: [A, C, D]
---

以下关于 `std::map::find()` 与 `operator[]` 的区别，哪些说法正确？（多选）

A. `find(key)` 若键不存在，返回 `end()`，不插入新元素
B. `find(key)` 若键不存在，会插入默认值并返回其迭代器
C. `operator[](key)` 若键不存在，会插入默认构造的值
D. 对 `const` 修饰的 `map` 对象，不能使用 `operator[]`，但可以使用 `find()`
