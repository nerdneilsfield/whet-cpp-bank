---
qid: cpp-real-multi-002
type: multi
kp: [cpp-iterators, cpp-containers]
primary_kp: cpp-iterators
difficulty: medium
answer_key: [A, B, D]
tags: [interview-real, multi-vendor]
---
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin() + 2;   // 指向 3
```
以下哪些操作**一定会**使 `it` 失效（多选）？

A. `v.push_back(6)` 触发了重分配（capacity 不足）
B. `v.insert(v.begin(), 0)`（在 it 之前插入）
C. `v.reserve(v.size() + 1)` 后 `push_back(6)`
D. `v.erase(v.begin())`（删除 it 之前的元素）
E. 仅读取 `v[0]` 或 `v[4]`

---

**解析：**

正确答案：**A、B、D**。

**vector 迭代器失效规则：**

**插入操作（insert / push_back / emplace_back）：**
- **若触发重分配**（size 即将超过 capacity）→ **所有**迭代器、指针、引用失效
- **若不触发重分配** → 插入点**之前**的迭代器有效，插入点**及之后**的迭代器失效

**删除操作（erase / pop_back）：**
- 被删除元素及**之后**的所有迭代器失效

**A 正确：** push_back 触发重分配 → 所有迭代器失效，it 失效

**B 正确：** insert 在 begin() 位置，it 在它之后 → it 失效（即使没重分配也失效，因为元素后移）

**C 错误：** reserve 后 capacity 充足，push_back 不重分配；且 it 在插入点之前 → **it 仍然有效**

**D 正确：** erase(begin()) 删除位置 0 → it（位置 2）在其之后 → 失效

**E 错误：** 读取不修改容器，不影响迭代器

**完整失效表格：**

| 操作 | vector | deque | list | set/map |
|------|--------|-------|------|---------|
| insert（不重分配） | 插入点后失效 | 全部失效 | 不失效 | 不失效 |
| insert（重分配） | 全部失效 | — | — | — |
| erase | 删除点及后失效 | 全部失效 | 仅指向被删 | 仅指向被删 |

**来源：** 阿里 / 字节 STL 迭代器失效经典考题（参考：cppreference）