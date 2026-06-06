---
qid: cpp-iv-stl-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [字节跳动, Google]
rubric:
  - 说清 vector 插入/扩容使指向元素的迭代器全部失效，erase 使被删位置之后的迭代器失效
  - 说清 map/set 任何插入不使现有迭代器失效，erase 只使被删节点的迭代器失效
  - 说清 list 任何插入不使迭代器失效，erase 只使被删节点的迭代器失效
  - 说出 unordered_map rehash 使所有迭代器失效，非 rehash 的插入也可能触发 rehash
  - 举出迭代器失效导致 UB 的典型 bug（循环中 erase）及正确写法
---

# 迭代器失效规则：`vector` / `map` / `list` 各在什么操作后失效？

## 问题

C++ STL 中不同容器的迭代器失效（iterator invalidation）规则不同。请分别说明 `vector`、`map`（及 `unordered_map`）、`list` 在插入和删除操作后迭代器的失效情况，并给出一个常见 bug 示例。

## 参考答案

### `std::vector`

**插入（`insert` / `push_back` / `emplace_back`）**：
- 若触发**扩容**（`size == capacity`）：所有迭代器、指针、引用**全部失效**（底层内存地址改变）。
- 若未扩容，但在中间/头部插入：插入位置及其**之后**的迭代器失效（元素被向后移动）；插入位置之前的迭代器有效。
- `push_back` / `emplace_back` 未扩容时：所有已有迭代器保持有效。

**删除（`erase`）**：被删元素及其**之后**的迭代器失效（元素前移），被删元素之前的迭代器有效。`erase` 返回指向下一个有效元素的迭代器。

### `std::map` / `std::set`（红黑树）

**插入**：不改变已有节点地址，所有现有迭代器**不失效**。

**删除（`erase`）**：只使**被删节点的迭代器**失效；所有其他节点的迭代器仍有效。这是红黑树节点独立分配带来的稳定性优势。

### `std::unordered_map` / `std::unordered_set`（哈希表）

**插入（非 rehash）**：若插入后 `load_factor ≤ max_load_factor`，不触发 rehash，现有迭代器**保持有效**。

**插入（触发 rehash）**：rehash 重建整个桶数组，所有迭代器**全部失效**。注意：单次插入可能隐式触发 rehash，调用者无法预知（除非已 `reserve`）。

**删除（`erase`）**：只使被删元素的迭代器失效。

### `std::list` / `std::deque`

**`list`**：
- 插入：任何位置插入都不使现有迭代器失效（节点独立分配）。
- 删除：只使被删节点的迭代器失效。`list` 是迭代器最稳定的序列容器。

**`deque`**：
- 头/尾插入：使所有迭代器失效（中控 map 可能重分配），但指向元素的引用/指针有效（元素未移动）。（注意：迭代器和引用的失效规则不同！）
- 中间插入/删除：所有迭代器和引用都失效。
- 仅 `push_back` / `push_front`：迭代器失效，但元素引用有效。

### 典型 Bug：循环中 erase

```cpp
// 错误：erase 后 it 已失效，++it 是 UB
for (auto it = v.begin(); it != v.end(); ++it) {
    if (should_remove(*it)) v.erase(it);  // BUG
}

// 正确：利用 erase 返回值
for (auto it = v.begin(); it != v.end(); ) {
    if (should_remove(*it)) it = v.erase(it);
    else ++it;
}

// 或者用 erase-remove idiom
v.erase(std::remove_if(v.begin(), v.end(), should_remove), v.end());
```

对于 `map`/`list`，由于删除不影响其他迭代器，循环中 `erase` 后 `++it` 是安全的，但用返回值的写法更通用。

### 速查表

| 容器 | 插入失效 | 删除失效 |
|------|--------|--------|
| `vector` | 扩容→全部；否则→插入点后 | 删除点及之后 |
| `map/set` | 不失效 | 仅被删节点 |
| `unordered_map` | rehash→全部；否则→不失效 | 仅被删节点 |
| `list` | 不失效 | 仅被删节点 |
| `deque` 头尾插 | 迭代器失效，引用有效 | 中间删→全部失效 |
