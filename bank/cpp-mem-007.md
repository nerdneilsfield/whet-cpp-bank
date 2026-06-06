---
qid: cpp-mem-007
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: A
---

# `std::weak_ptr<T>` 的主要用途是？

A. 打破 `shared_ptr` 循环引用，避免内存泄漏
B. 替代裸指针，提供自动内存管理
C. 提供比 `shared_ptr` 更快的引用计数
D. 将 `unique_ptr` 转换为可拷贝的指针

<!--
weak_ptr 不增加引用计数，用于观察 shared_ptr 管理的对象，
打破 A→B、B→A 的循环引用。答案 A。
-->
