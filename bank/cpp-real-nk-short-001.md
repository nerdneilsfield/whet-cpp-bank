---
qid: cpp-real-nk-short-001
type: short
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: hard
tags: [interview-real, nowcoder]
rubric:
  - 链地址法（2 分）
  - load_factor + rehash 触发（2 分）
  - rehash 时迭代器失效（1 分）
  - 复杂度对比（2 分）
  - 顺序性差异（1 分）
  - 自定义类型需要 hash 特化（1 分）
---

请详细描述 `std::unordered_map` 的内部实现机制，包括：
1. 底层数据结构
2. 哈希冲突如何解决
3. 何时触发 rehash 以及 rehash 的开销
4. 与 `std::map` 在时间复杂度和适用场景上的对比

---

**解析（参考答案）：**

**1. 底层数据结构**

`unordered_map` 是哈希表（hash table）实现：
- 一个**桶数组**（`vector<bucket>` 等价物）
- 每个桶是一个**链表**（separate chaining）
- 每个节点存键值对 + next 指针
- 维护额外的全局迭代器链（C++ 标准要求 begin/end 遍历所有元素）

**2. 哈希冲突解决**

使用**链地址法**（separate chaining）：

- 计算 `hash(key) % bucket_count` 得桶下标
- 桶内用链表存所有 hash 落入同一桶的元素
- 查找时遍历链表用 `key_equal` 比较
- C++ 标准强制链表实现（接口暗含），不允许开放地址法（虽然 absl::flat_hash_map 等非标准实现使用开放地址法以获得 cache 优势）

**3. Rehash 时机和开销**

- 维护 `load_factor = size / bucket_count`，默认 `max_load_factor = 1.0`
- 当插入后 `load_factor > max_load_factor`，触发 rehash
- Rehash：bucket_count 通常扩为下一个素数（约 2 倍），所有元素重新哈希到新桶
- **开销**：O(N)，且会**使迭代器失效**

可以通过 `reserve(N)` 预分配桶，避免反复 rehash。

**4. 与 std::map 对比**

| 维度 | unordered_map (哈希) | map (红黑树) |
|------|---------------------|--------------|
| 平均查找 | O(1) | O(log n) |
| 最坏查找 | O(n)（全冲突） | O(log n) |
| 元素顺序 | 无序 | 按 key 有序 |
| 范围查询 | 不支持 | 支持（lower_bound/upper_bound） |
| 内存开销 | 桶数组 + 链表节点（较大） | 树节点（较小） |
| Cache 友好 | 一般 | 较差（节点分散） |
| 插入/删除常数 | 较大（hash 计算） | 中等 |

**适用场景**：
- 频繁查找但无顺序需求 → unordered_map
- 需要顺序遍历或范围查询 → map
- 键类型自定义需注意 unordered_map 要提供 `hash<T>` 特化

**rubric:**
- 链地址法（2 分）
- load_factor + rehash 触发（2 分）
- rehash 时迭代器失效（1 分）
- 复杂度对比（2 分）
- 顺序性差异（1 分）
- 自定义类型需要 hash 特化（1 分）
- cache 友好性讨论（1 分）

**来源：** 牛客网 C++ STL 高频面试题 / cppreference / SGI STL 源码