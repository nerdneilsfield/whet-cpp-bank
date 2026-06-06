---
qid: cpp-conc-multi-002
type: multi
kp: [cpp-concurrency]
difficulty: medium
answer_key: [A, C]
---
关于数据竞争（data race），**哪些情况构成数据竞争**？（多选）

A. 两个线程同时写同一个非原子变量，且无同步。
B. 两个线程并发地通过 `std::shared_ptr` 调用 `lock()` / 复制（各自副本）。
C. 一个线程读、另一个线程写同一个非原子变量，且无同步。
D. 多线程同时读同一个 const 数据，无写入。

---

**解析：**

A 正确：典型的数据竞争（write-write）。
B 错误：复制各自的 `shared_ptr` 副本仅修改原子引用计数，本身线程安全。
C 正确：read-write 冲突，仍是数据竞争。
D 错误：只读访问不是数据竞争。