---
qid: cpp-real-multi-008
type: multi
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: medium
answer_key: [A, B, D]
tags: [interview-real, multi-vendor]
---
```cpp
std::map<int, int>           m1;   // 红黑树，有序
std::unordered_map<int, int> m2;   // 哈希表，无序
```
关于 `std::map` vs `std::unordered_map` 的选型，以下说法**正确**的是（多选）：

A. 需要按 key 排序遍历时选 map；只需快速查找时选 unordered_map
B. map 操作复杂度为 O(log n)；unordered_map 平均 O(1)，最坏 O(n)（哈希冲突严重时）
C. map 的查找在所有情况下都比 unordered_map 慢
D. unordered_map 要求 key 类型可哈希（提供 `std::hash<Key>` 特化或自定义），map 要求 key 可比较（`<` 操作符或自定义比较器）
E. 两者在内存占用上完全相同

---

**解析：**

正确答案：**A、B、D**。

**核心对比：**

| 维度 | std::map | std::unordered_map |
|------|----------|---------------------|
| 底层 | 红黑树 | 哈希表（开链法） |
| 元素有序 | 是（按 key 排序） | 否（哈希顺序） |
| 平均查找 | O(log n) | O(1) |
| 最坏查找 | O(log n) | O(n)（哈希冲突极端） |
| 范围查询 | 支持（lower/upper_bound） | 不支持高效范围 |
| 内存 | 每节点 = key+value + 3 指针 + color | 桶数组 + 链表节点 |
| 缓存友好 | 较差（树节点散在堆中） | 较好（桶数组连续） |
| 迭代器失效（insert） | 不失效 | 可能失效（rehash 时） |

**A 正确：** 选型核心依据。要遍历有序、范围查询、按序输出 → map；只查找/插入 → unordered_map。

**B 正确：** 复杂度的标准描述。最坏情况发生在哈希函数差、攻击场景下（DoS via hash collision）。

**C 错误：** 在**小数据集**下，map 可能比 unordered_map 快（避免哈希计算开销，缓存友好）。一般经验：n < 100 时差距很小或 map 更快。

**D 正确：** map 用 `Compare`（默认 `std::less<Key>`，要求 key 支持 `<`）；unordered_map 用 `Hash` + `KeyEqual`（默认 `std::hash<Key>` + `std::equal_to<Key>`）。自定义 key 类型必须提供相应支持。

**E 错误：** 内存差异大。unordered_map 通常**占用更多内存**（桶数组 + 链表节点开销），但缓存更友好。

**实际选型建议：**
- 默认用 unordered_map（更快）
- 有序需求 → map
- key 是字符串且短小 → unordered_map 哈希开销可忽略
- 极端追求性能 → 考虑第三方哈希表（如 robin_hood、absl::flat_hash_map）

**来源：** 跨厂 STL 选型经典题（参考：cppreference）