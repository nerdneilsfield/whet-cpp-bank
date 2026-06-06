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

## 解析

正确选项是 A、B、D。std::remove 是通用算法，只重排元素并返回逻辑末尾，尾部元素有效但值未指定，容器大小不变。它不要求 vector；C++20 的 std::erase/std::erase_if 正是对 erase-remove 惯用法的简化。
