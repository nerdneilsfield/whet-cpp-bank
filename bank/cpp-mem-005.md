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

## 解析

正确答案是 B，`unique_ptr` 表示独占所有权，不能拷贝，只能移动转移所有权。`shared_ptr` 表示共享所有权，通过控制块中的引用计数决定对象何时销毁。两者的核心差别不是存储位置或引入标准版本，而是所有权语义和运行时开销。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
