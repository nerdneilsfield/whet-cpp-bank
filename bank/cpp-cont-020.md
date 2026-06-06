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

## 解析

正确答案是 A、C、D。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。 A 正确：｀find(key)｀ 若键不存在，返回 ｀end()｀，不插入新元素；B 错误：｀find(key)｀ 若键不存在，会插入默认值并返回其迭代器；C 正确：｀operator[](key)｀ 若键不存在，会插入默认构造的值；D 正确：对 ｀const｀ 修饰的 ｀map｀ 对象，不能使用 ｀operator[]｀，但可以使用 ｀find()｀。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
