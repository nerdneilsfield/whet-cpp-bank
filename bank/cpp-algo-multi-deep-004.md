---
qid: cpp-algo-multi-deep-004
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B]
---

关于 `std::stable_sort` 与 `std::sort`，下列哪些**正确**？（多选）

A. `std::stable_sort` 保证相等元素的相对顺序不变
B. `std::sort` 平均/最坏 O(n log n)（C++11 起最坏也是 n log n），不保证稳定
C. `std::stable_sort` 复杂度严格优于 `std::sort`
D. 两者都可用于 `std::list`

---

**解析：**

- A ✅：稳定性是 stable_sort 的核心契约。
- B ✅：C++11 起 `std::sort` 最坏复杂度也是 O(n log n)（典型实现 introsort：quicksort + 深度阈值切 heapsort）。C++03 仅保证平均。
- C ❌：`stable_sort` 是 O(n log n) 至 O(n log² n)（取决于辅助内存），常数项通常更大；并不严格优于 `std::sort`。
- D ❌：两者都要 RandomAccessIterator；`list` 用其成员 `sort()`，那才是稳定归并排序。

实际：需稳定性才用 stable_sort，否则 `std::sort` 更快、内存更少。
