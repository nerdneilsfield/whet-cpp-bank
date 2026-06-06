---
qid: cpp-real-en-012
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: D
tags: [interview-real, interviewbit]
---
以下哪项不是防止 race condition（竞态条件）的有效手段？

A. 使用 `std::mutex` 保护共享数据
B. 使用 `std::atomic<T>` 对简单变量进行原子操作
C. 使用 `std::shared_mutex` 实现读写锁
D. 使用 `volatile` 关键字声明共享变量

---

**解析：**

Race condition 指多个线程同时访问共享数据且至少有一个是写操作，导致结果依赖于线程执行顺序。

常见预防手段：
- **`std::mutex` / `std::lock_guard`**：互斥锁保护临界区
- **`std::atomic<T>`**：原子操作，无锁线程安全
- **读写锁（`std::shared_mutex`）**：多读单写

**`volatile` 不能防止 race condition**。`volatile`只阻止编译器优化，不提供任何内存排序保证或原子性。线程安全的标志位应使用 `std::atomic<bool>` 而不是 `volatile bool`。

**来源：** InterviewBit "C++ Interview Questions" — Race Condition