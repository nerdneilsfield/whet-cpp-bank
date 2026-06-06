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

## 解析

正确答案是 A、C、D。A 避免裸 `new` 并提升异常安全；C 是 RAII 的核心做法；D 用 `weak_ptr` 打破强引用环。B 错在 `new[]` 必须配 `delete[]`，E 错在依赖每个出口手动释放，遇到异常或提前返回时很容易泄漏。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
