---
qid: cpp-mem-019
type: multi
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: [A, C, D]
---

# 下列哪些做法符合 C++ 现代内存管理的最佳实践？（多选）

A. 优先使用 `std::make_unique` / `std::make_shared`，而非裸 `new`
B. 用 `delete` 释放 `new[]` 分配的数组
C. 将资源所有权封装在 RAII 对象（如智能指针或自定义类）中
D. 用 `std::weak_ptr` 打破 `shared_ptr` 的循环引用
E. 在每个函数结尾手动调用 `delete` 以确保释放

<!--
A — 推荐，减少裸 new 的异常安全问题。
B — 错误，delete[] 才正确。
C — RAII 核心实践。
D — weak_ptr 解循环引用。
E — 错误，应依赖 RAII 而非手动管理。
答案：A C D
-->
