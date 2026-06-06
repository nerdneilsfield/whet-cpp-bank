---
qid: cpp-mem-hard-003
type: single
kp: [cpp-memory-mgmt]
difficulty: hard
answer_key: B
---

下列关于 `std::make_shared<T>(args...)` 的线程安全性描述，最准确的是？

A. `make_shared` 构造的 `shared_ptr` 本身可被多线程同时写入而无需同步
B. `make_shared` 单次调用是线程安全的；同一 `shared_ptr` 实例的非 `const` 成员仍需外部同步，但**不同**实例间的引用计数操作彼此线程安全
C. `make_shared` 内部使用全局锁，因此多线程并发调用会成为瓶颈
D. 因为合并分配，`make_shared` 产生的对象不能被多线程读

## 解析

C++ 标准对 `shared_ptr` 的线程保证是：**控制块的引用计数是原子的**，因此**不同**的 `shared_ptr` 实例（即使指向同一对象）可在多线程间各自拷贝/析构，互不干扰；但**同一**实例的 `reset` / `operator=` 等非 `const` 操作仍需外部同步（或使用 `std::atomic<shared_ptr>`，C++20）。`make_shared` 本身只是一个构造工厂，无全局锁、亦不限制后续多线程读对象。A 错误：同一实例无内置写写同步；C 错误：实现使用原子操作而非全局锁；D 错误：合并分配不影响可见性。
