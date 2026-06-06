---
qid: cpp-conc-multi-001
type: multi
kp: [cpp-concurrency]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::atomic` 提供的保证，**哪些说法是正确的**？（多选）

A. 对原子变量的 load/store 操作不会被撕裂（torn read/write）。
B. `std::atomic<T>` 默认使用 `memory_order_seq_cst`，提供最强内存顺序。
C. `std::atomic<T>::is_lock_free()` 一定返回 true。
D. `compare_exchange_weak` 可能伪失败，需要在循环中使用。

---

**解析：**

A 正确：原子操作保证读写不可分割。
B 正确：未显式指定时使用顺序一致性。
C 错误：原子性可能由互斥锁实现，不一定 lock-free（如 `atomic<LargeStruct>`）。
D 正确：`compare_exchange_weak` 允许偶然伪失败（spurious failure），通常配合循环。