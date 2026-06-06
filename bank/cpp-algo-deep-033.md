---
qid: cpp-algo-deep-033
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

C++17 `std::reduce` 与 `std::accumulate` 的**关键区别**是？

```cpp
std::vector<int> v{1,2,3,4,5};
auto a = std::accumulate(v.begin(), v.end(), 0);  // 严格左折叠
auto r = std::reduce(v.begin(), v.end(), 0);      // ?
```

A. 完全相同，`reduce` 只是新名字
B. `reduce` 允许**任意求值顺序与重排**，要求二元操作满足**结合律与交换律**；可加 `std::execution::par` 并行
C. `reduce` 更慢，只在并行库中存在
D. `reduce` 不接受初值

---

**解析：**

`std::accumulate` 是**严格左折叠**：`((((init + v[0]) + v[1]) + v[2]) + ...)`。顺序固定，因此对**浮点求和**结果是确定的，但**无法并行**。

`std::reduce(policy, first, last, init, binary_op)` 不规定结合顺序，可任意重排——因此要求 `binary_op` **结合律**（实际并行实现常假定交换律）。可加并行策略，多核分块归约。

对浮点：`reduce` 结果可能因实现/线程数而变化（数值不可重复）；`accumulate` 重复。

并行加和的正确选择是 `std::reduce(std::execution::par, v.begin(), v.end(), 0.0)`。
