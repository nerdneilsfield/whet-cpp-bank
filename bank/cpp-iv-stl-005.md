---
qid: cpp-iv-stl-005
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Meta, Amazon]
rubric:
  - 说清 map 有序、unordered_map 无序的根本差异
  - 给出选 map 的场景：需要有序迭代、范围查询、键类型无 hash 实现
  - 给出选 unordered_map 的场景：纯查找/插入频繁、键类型 hash 代价低
  - 提及实际性能差距（常数因子、缓存局部性）而非只谈 O 记号
  - 提及 unordered_map 的额外风险：哈希碰撞攻击、rehash 导致迭代器失效
---

# `std::map` vs `std::unordered_map`：如何选择？

## 问题

`std::map` 和 `std::unordered_map` 各有什么特点？在工程实践中，如何决定用哪一个？

## 参考答案

### 核心对比

| 维度 | `std::map` | `std::unordered_map` |
|------|-----------|----------------------|
| 底层结构 | 红黑树 | 哈希表（桶+链表） |
| 键的顺序 | 有序（升序） | 无序 |
| 查找/插入/删除 | O(log n) | 平均 O(1)，最坏 O(n) |
| 内存布局 | 节点散列堆上，缓存不友好 | 桶数组连续，但链表节点同样散落 |
| 迭代器稳定性 | 插入/删除不影响其他迭代器 | rehash 使所有迭代器失效 |
| 键要求 | 需 `operator<`（或自定义比较器） | 需 `std::hash` 特化 + `operator==` |

### 选 `std::map` 的场景

1. **需要有序迭代**：如按 key 顺序输出所有条目、TopK 查询。
2. **需要范围查询**：`lower_bound` / `upper_bound` 依赖有序性，`unordered_map` 不支持。
3. **键类型没有好的哈希函数**：如复合结构体、自定义类，编写正确且高效的 `std::hash` 非易事。
4. **需要确定性的最坏性能**：`map` 的 O(log n) 是硬保证；`unordered_map` 在哈希退化时可能变 O(n)。
5. **元素数量极小（< 数十个）**：两者性能差异可忽略，`map` 代码更安全。

### 选 `std::unordered_map` 的场景

1. **频繁的 key 查找/插入，且 key 有高质量 hash**：字符串、整数等，平均 O(1) 吞吐显著优于 O(log n)。
2. **不需要键有序**：纯作字典（dictionary）使用。
3. **数据规模大（>10³~10⁴）时**：O(log n) 的常数在大数据量下与 O(1) 差距明显；实测整数 key 下 `unordered_map` 吞吐约 3~5× 快于 `map`。

### 实际性能注意事项

- `map` 节点全部分配在堆上，每次访问都可能 cache miss，实际延迟往往比 O(log n) 理论值更差。
- `unordered_map` 的链表节点同样散落，高负载时也有缓存问题。若极度追求性能，考虑 `absl::flat_hash_map`（开放寻址，缓存友好）。
- `unordered_map` 默认 `max_load_factor = 1.0`，对频繁插入的场景建议 `reserve` 预分配，避免 rehash 开销和迭代器失效。

### 工程决策口诀

> 需要有序 → `map`；纯查字典且 key 有 hash → `unordered_map`；不确定 → `map` 更安全，性能不够再换。
