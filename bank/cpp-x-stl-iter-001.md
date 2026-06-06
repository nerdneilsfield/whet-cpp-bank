---
qid: cpp-x-stl-iter-001
type: single
kp: [cpp-stl-basics, cpp-iterators]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: A
---

下列对 `std::vector` 的操作中，哪一个 **不会** 使所有已有迭代器、引用、指针失效（在容量充足、不触发重新分配的前提下）？

```cpp
#include <vector>

std::vector<int> v{1, 2, 3, 4, 5};
v.reserve(100);   // 容量充足，假设 100

auto it = v.begin() + 2;     // 指向 3

void test() {
    v.push_back(6);          // (A) 末尾追加
    v.insert(v.begin(), 0);  // (B) 头部插入
    v.erase(v.begin() + 1);  // (C) 删除中间元素
    v[1] = 99;               // (D) 修改元素值
}
```

A. (A) 和 (D)
B. (A)、(B)、(D)
C. 只有 (D)
D. 只有 (A)

---

## 解析

**`std::vector` 的迭代器/引用/指针失效规则**（[vector.modifiers]）：

1. **重新分配**（`size > capacity`）：所有迭代器、引用、指针 **全部失效**。
2. **`push_back`/`emplace_back`**：若不引起重新分配，**只有 `end()` 迭代器失效**，其他迭代器和引用保持有效。
3. **`insert`/`emplace`**：插入点 **及其之后** 的所有迭代器、引用、指针失效。即使不重新分配，因为后续元素被向后移动。
4. **`erase`**：删除点 **及其之后** 的所有迭代器、引用、指针失效。
5. **`assign`/`resize`** 可能引起重新分配，全部失效（或部分）。
6. **修改元素值**（如 `v[i] = x`）：**完全不影响** 迭代器/引用/指针，它们指向相同的元素槽位，只是值变了。

逐项分析：

- **(A) `push_back(6)`**：容量充足（capacity 100），不重新分配。只 `end()` 失效，`it`（指向下标 2）仍有效。**不失效**。
- **(B) `insert(v.begin(), 0)`**：在头部插入，插入点是 `begin()`，**所有** 后续迭代器（包括 `it`）全部失效。
- **(C) `erase(v.begin() + 1)`**：删除下标 1 的元素，删除点之后（下标 ≥ 1）的所有迭代器失效，`it`（下标 2）失效。
- **(D) `v[1] = 99`**：只修改值，迭代器/引用/指针全部保持有效。

所以 (A) 和 (D) 都不会让 `it` 失效。

实践建议：
- 在循环中插入/删除时，使用 `it = v.erase(it)`（erase 返回下一个有效迭代器）。
- 频繁中部插入/删除请用 `std::list` 或 `std::deque`。
- 已知容量请用 `reserve` 预分配，避免 push_back 触发重分配开销。