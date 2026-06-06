---
qid: cpp-mem-008
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: B
---

# 相比 `std::shared_ptr<T>(new T(args))` ，`std::make_shared<T>(args)` 的优势是？

A. `make_shared` 支持自定义删除器，`shared_ptr(new T)` 不支持
B. `make_shared` 一次分配同时存储对象和控制块，减少内存分配次数，更高效
C. `make_shared` 不增加引用计数，性能更好
D. `make_shared` 返回 `unique_ptr`，所有权更清晰

<!--
make_shared 将对象内存和控制块（引用计数）合并为单次 allocation，
避免两次 new；同时在 new T 抛异常时也更安全。答案 B。
-->

## 解析

正确答案是 B，`make_shared` 通常把对象和控制块合并为一次内存分配，减少分配次数并改善局部性。直接 `shared_ptr<T>(new T(...))` 往往需要对象和控制块两次分配，还更容易写出异常安全问题。注意 `make_shared` 不等于不计数，也不会返回 `unique_ptr`。
