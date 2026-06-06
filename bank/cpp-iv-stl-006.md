---
qid: cpp-iv-stl-006
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google]
rubric:
  - 说清 vector 连续内存 vs list 节点分散的本质差异
  - 解释缓存局部性（cache locality）是 vector 快的核心原因
  - 说出 list 的 O(1) 任意位置插入/删除优势及其前提（已有迭代器）
  - 给出 vector 随机访问 O(1) vs list O(n) 的对比
  - 说出 list 几乎无实际使用场景（现代硬件上 vector+erase 往往更快）
---

# `std::list` vs `std::vector`：性能特征与选用

## 问题

`std::list` 和 `std::vector` 在内存布局和性能上有哪些根本差异？为什么大多数场景下 `vector` 实际性能更好，即使 `list` 的插入/删除理论上是 O(1)？

## 参考答案

### 内存布局差异

**`std::vector`**：元素在堆上**连续存储**，类似 C 数组。

```
[e0][e1][e2][e3][e4]...  ← 一块连续内存
```

**`std::list`**：双向链表，每个元素是独立的堆节点，存储 `(prev*, next*, value)`。

```
heap: [e0]←→[e1]←→[e2]←→[e3]  ← 节点分散在内存各处
```

### 为什么 vector 更快：缓存局部性

现代 CPU 的缓存行（cache line）通常 64 字节。访问 `vector[i]` 时，CPU 会将相邻的 8~16 个 `int` 一起加载进 L1/L2 缓存，后续访问几乎全部命中缓存（prefetch 也有效）。

访问 `list` 节点时，每个节点的地址是随机的（malloc 分散），每次 `++it` 几乎必然 **cache miss**，需要 ~100 ns 的内存访问，而缓存命中只需 ~1 ns。

**实测数据**（参考 Bjarne Stroustrup 等人的 benchmark）：在随机访问或顺序遍历场景下，`vector` 比 `list` 快 **5~20 倍**，差距随数据量增大。

### 操作复杂度对比

| 操作 | `vector` | `list` |
|------|---------|--------|
| 随机访问 `[i]` | O(1) | O(n) |
| 尾部插入 | 均摊 O(1) | O(1) |
| 中间插入（已有迭代器）| O(n)（移动元素） | O(1) |
| 中间插入（按值查找后）| O(n)+O(n) | O(n)+O(1) |
| 删除中间元素（已有迭代器）| O(n) | O(1) |
| 遍历 | O(n)，缓存极友好 | O(n)，缓存极差 |
| 内存开销 | 小（无指针） | 大（2 个指针/节点） |

### "list 插入 O(1)"的前提

`list` 的 O(1) 插入要求**已持有插入位置的迭代器**。若需先查找再插入（最常见情形），总代价仍是 O(n)，而且由于 cache miss 导致的常数远大于 vector 的 O(n) 移动（内存 memmove 是极快的连续操作）。

### list 的有效使用场景（极少）

1. **splice 操作**：将一个 list 的部分节点 O(1) 接入另一个 list——`vector` 做不到。
2. **插入/删除不能使其他迭代器失效**：`list` 的迭代器在任何插入/删除后都不失效（除被删节点自身）。
3. **元素不可移动/不可拷贝**：某些特殊类型只能在固定地址存活。

### 结论

绝大多数场景下优先选 `vector`。"我需要频繁中间插入"通常不是选 `list` 的理由——先看能否用 `vector + 批量 erase` 或 `std::deque` 替代，它们的缓存友好性均优于 `list`。
