---
qid: cpp-real-nk-005
type: single
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: B
tags: [interview-real, nowcoder]
---

`std::unordered_map` 处理哈希冲突使用的方法是：

A. 开放地址法（线性探测）
B. 链地址法（拉链法，每个桶是一个链表）
C. 再哈希法（rehashing）
D. 完美哈希（perfect hashing）

---

**解析：**

C++ 标准要求 `unordered_map` 必须使用**链地址法**（separate chaining）解决冲突。原因：

1. 标准要求迭代器在 rehash 之外的操作下保持稳定（链表节点不动）
2. `bucket_count`、`bucket_size`、`local_iterator` 等 API 暗含了"桶 = 链表"的实现模型
3. `load_factor` 可以 > 1（开放地址法不可能）

冲突时同一个桶的元素串成链表，查找复杂度退化为 O(链长)。当 `load_factor > max_load_factor` 时触发 rehash，桶数量通常翻倍。

注意：Google 的 `absl::flat_hash_map` 才使用开放地址法（cache 更友好），但这是非标准实现。

**来源：** 牛客网 C++ STL 高频面试题 / cppreference

## Explanation

正确答案是 B。
注意：Google 的 absl::flat_hash_map 才使用开放地址法（cache 更友好），但这是非标准实现。
