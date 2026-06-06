---
qid: cpp-algo-multi-deep-001
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B, D]
---

关于 `std::remove` 与 erase-remove 惯用法，下列哪些**正确**？（多选）

```cpp
std::vector<int> v{1,2,3,2,4,2};
v.erase(std::remove(v.begin(), v.end(), 2), v.end());
```

A. `std::remove` 本身不改变容器 size，只重排元素并返回新逻辑末尾迭代器
B. `[new_end, old_end)` 区间的元素值处于"有效但未指定"状态
C. `std::remove` 要求容器为 `vector`
D. C++20 引入 `std::erase(container, value)` 简化此惯用法

---

**解析：**

- A ✅：`std::remove` 是 `<algorithm>` 通用算法，无法访问容器，自然无法 `pop_back`。
- B ✅：被移动赋值过的尾部元素是有效但未指定状态——可析构、可重新赋值。
- C ❌：可用于任意 ForwardIterator 范围；连原生数组也能用。
- D ✅：C++20 `std::erase` 和 `std::erase_if` 直接对容器做"擦除值/擦除满足谓词"，省去 idiom。

注意：对 `std::list` 应直接用成员 `remove`/`remove_if`，O(n) 且不需要节点移动。
