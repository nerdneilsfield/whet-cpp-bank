---
qid: cpp-cont-fill-med-001
type: fill
kp: [cpp-containers]
difficulty: medium
answer_key: "1"
---
`std::unordered_map` 平均查找复杂度是 O(___)。

---

**解析：**

`std::unordered_map` 基于哈希表实现，在哈希函数均匀分布且负载因子合理的条件下，查找、插入、删除的平均时间复杂度均为 O(1)。但在最坏情况（哈希碰撞严重）下可能退化为 O(n)。C++ 标准要求其支持前向迭代器，平均 O(1) 并非严格保证，而是实践预期。