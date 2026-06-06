---
qid: cpp-algo-002
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下哪项关于 `std::sort` 的描述是**正确**的？

A. `std::sort` 是稳定排序，相等元素的相对顺序保持不变
B. `std::sort` 不保证稳定性，相等元素的相对顺序可能改变
C. `std::sort` 要求双向迭代器（bidirectional iterator）即可
D. `std::sort` 的时间复杂度保证为 O(n log n) 且为稳定排序

## Explanation

正确答案为 B，因为“`std::sort` 不保证稳定性，相等元素的相对顺序可能改变”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
