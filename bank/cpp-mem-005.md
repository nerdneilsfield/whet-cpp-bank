---
qid: cpp-mem-005
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: B
---

# `std::unique_ptr<T>` 与 `std::shared_ptr<T>` 最本质的区别是？

A. `unique_ptr` 存储在栈，`shared_ptr` 存储在堆
B. `unique_ptr` 独占所有权（不可拷贝），`shared_ptr` 共享所有权（引用计数）
C. `unique_ptr` 支持自定义删除器，`shared_ptr` 不支持
D. `shared_ptr` 是 C++11 引入的，`unique_ptr` 是 C++14 引入的

<!--
所有权语义是核心区别。unique_ptr 不可拷贝只可移动；
shared_ptr 通过引用计数允许多个共同持有。答案 B。
-->
