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

## 解析

正确选项是 A、B。stable_sort 保证等价元素的相对顺序不变，sort 不保证稳定但复杂度为 O(n log n)。stable_sort 并不严格优于 sort，通常常数和内存成本更高。两者都要求随机访问迭代器，list 应用成员 sort。
