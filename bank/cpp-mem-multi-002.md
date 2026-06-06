---
qid: cpp-mem-multi-002
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, C]
---
关于 `std::shared_ptr` 的线程安全性，**哪些说法是正确的**？（多选）

A. 对同一个 `shared_ptr` 对象的引用计数增减是线程安全的。
B. 多个线程同时对**同一个** `shared_ptr` 实例进行 `reset()` 或赋值是安全的，不需要外部同步。
C. 不同线程通过各自的 `shared_ptr` 实例（指向同一对象）读取控制块是安全的。
D. `shared_ptr` 所管理的对象本身的访问是线程安全的，由 `shared_ptr` 保护。

---

**解析：**

A 正确：控制块中的引用计数使用原子操作，线程安全。
B 错误：修改同一 `shared_ptr` 实例（如 `reset`、赋值）不是线程安全的，需要外部同步或使用 `std::atomic<shared_ptr>`。
C 正确：多个线程通过各自的副本访问控制块是安全的，这是 `shared_ptr` 设计目标之一。
D 错误：`shared_ptr` 只保证控制块的线程安全，被管理对象本身的并发访问仍需用户自行同步。
