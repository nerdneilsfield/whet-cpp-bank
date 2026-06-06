---
qid: cpp-iv-stl-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 字节跳动]
rubric:
  - 说清底层是哈希表（桶数组 + 链表/开放寻址）
  - 说出标准库实现用分离链接法（链表挂桶）
  - 说清哈希冲突的两种主流解法（链地址法 vs 开放寻址）及各自优劣
  - 说出负载因子（load_factor）与 rehash 触发条件（默认 max_load_factor = 1.0）
  - 说出最坏 O(n) 退化场景（所有 key 哈希到同一桶）及应对（好的哈希函数 / 随机种子）
---

# `std::unordered_map` 的底层实现？哈希冲突如何解决？

## 问题

`std::unordered_map` 的底层数据结构是什么？当多个 key 的哈希值相同时（哈希冲突），标准库如何处理？负载因子和 rehash 是怎么回事？

## 参考答案

### 底层结构：哈希表

`std::unordered_map` 的底层是**哈希表**，具体实现为**桶数组（bucket array）+ 链表（分离链接法）**。

结构示意：

```
bucket[0] -> (key1,val1) -> (key2,val2) -> nullptr
bucket[1] -> nullptr
bucket[2] -> (key3,val3) -> nullptr
...
bucket[N-1]
```

每个桶（bucket）是一个单链表的头指针。所有哈希到同一桶的元素串成一条链表。GCC libstdc++ 用一条全局单链表存所有元素，桶数组只存各桶的起始迭代器，以保证 `begin()` / `end()` 的 O(1) 和全局迭代的连续性。

### 哈希冲突的两种主流解法

**1. 分离链接法（Separate Chaining，标准库采用）**
- 桶内用链表（或其他结构）存所有冲突元素。
- 优点：删除简单，负载因子可超过 1.0，缓存不友好但实现直接。
- 缺点：链表节点分散在堆上，缓存命中率低。

**2. 开放寻址法（Open Addressing，标准库未采用）**
- 冲突时在桶数组内探测下一个空位（线性探测 / 二次探测 / 双重哈希）。
- 优点：数据紧凑，缓存局部性好（如 Swiss Table / abseil 的 `flat_hash_map`）。
- 缺点：负载因子必须 < 1，删除需"墓碑"标记，实现复杂。

### 负载因子与 rehash

**负载因子** = `size / bucket_count`。

标准库默认 `max_load_factor() == 1.0`。每次插入后若 `load_factor > max_load_factor`，触发 **rehash**：

1. 将桶数组扩大约 2 倍（`new_bucket_count ≥ size / max_load_factor`）。
2. 将所有元素重新映射到新桶（对新桶数取模）。
3. rehash 是 O(n) 操作，会使所有迭代器失效。

可通过 `reserve(n)` 预分配，避免插入过程中触发 rehash。

### 平均 vs 最坏复杂度

| 操作 | 平均 | 最坏 |
|------|------|------|
| 查找/插入/删除 | O(1) | O(n) |

最坏情况：攻击者构造哈希碰撞（所有 key 落同一桶），链表退化为 O(n)。缓解手段：使用随机种子的哈希函数（如 std::hash 在某些实现上加盐），或业务层限制输入来源。

### 与 `std::map` 的本质区别

`unordered_map` 不维护键的顺序，换来平均 O(1) 操作；`map` 维护有序性，保证 O(log n) 操作。
