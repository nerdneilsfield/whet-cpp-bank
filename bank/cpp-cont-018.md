---
qid: cpp-cont-018
type: multi
kp: [cpp-containers]
difficulty: easy
answer_key: [A, C]
---

以下关于 `std::list` 的说法，哪些是正确的？（多选）

A. 在已知迭代器位置插入元素的复杂度为 O(1)
B. 支持 `operator[]` 随机访问
C. 在 `list` 上插入元素不会导致任何迭代器失效
D. `list` 底层使用连续内存存储元素

## Explanation

正确答案是 A、C。`std::list` 是双向链表，迭代器位置插入删除快，但不支持随机访问。 A 正确：在已知迭代器位置插入元素的复杂度为 O(1)；B 错误：支持 ｀operator[]｀ 随机访问；C 正确：在 ｀list｀ 上插入元素不会导致任何迭代器失效；D 错误：｀list｀ 底层使用连续内存存储元素。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
