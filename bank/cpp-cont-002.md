---
qid: cpp-cont-002
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: C
---

`std::unordered_map` 与 `std::map` 最主要的区别是？

A. `unordered_map` 不支持迭代
B. `unordered_map` 只能存储整数键
C. `unordered_map` 基于哈希表，不保证元素有序
D. `unordered_map` 查找复杂度为 O(log n)

## 解析

正确答案是 C。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。选项 C 的表述“｀unordered_map｀ 基于哈希表，不保证元素有序”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
