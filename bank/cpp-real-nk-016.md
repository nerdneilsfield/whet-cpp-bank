---
qid: cpp-real-nk-016
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: easy
answer_key: B
tags: [interview-real, nowcoder]
---

`std::make_shared<T>(args...)` 相比 `std::shared_ptr<T>(new T(args...))` 的最大优势是：

A. 性能完全相同，只是写法更简洁
B. **只需要一次内存分配**（对象和控制块连续），减少分配开销并提升 cache 局部性
C. 可以避免循环引用
D. 自动支持自定义删除器

---

**解析：**

`make_shared` 内部使用一次 `::operator new` 分配 `sizeof(T) + sizeof(ControlBlock)` 的连续内存。

`shared_ptr<T>(new T)` 需要两次分配：
1. `new T` 分配对象
2. shared_ptr 构造时再 new 一个控制块

优势：
1. **性能**：分配次数减半，且释放也只需要一次
2. **cache 局部性**：对象和控制块相邻，访问引用计数时可能不需额外 cache line
3. **异常安全**：`f(shared_ptr<T>(new T), g())` 中，如果 `g()` 抛异常且 `new T` 已成功但 shared_ptr 还未构造，会泄漏；`make_shared` 整体是单一函数调用，无此问题

劣势：
1. 不支持自定义删除器
2. 对象内存释放可能延迟到 weak_ptr 也清零（控制块同块内存）

**来源：** 卡码笔记 / Effective Modern C++ Item 21