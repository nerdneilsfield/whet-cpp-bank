---
qid: cpp-real-en-013
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: C
tags: [interview-real, interviewbit]
---
关于 `std::mutex`、`std::lock_guard` 和 `std::unique_lock`，以下说法正确的是？

A. `std::lock_guard` 比 `std::mutex` 多提供了 `lock()` / `unlock()` 手动控制能力
B. `std::unique_lock` 是 `std::mutex` 的 RAII 封装，但必须在构造时加锁且不能提前解锁
C. `std::mutex` 是底层锁；`std::lock_guard` 是轻量 RAII 封装（构造加锁、析构解锁）；`std::unique_lock` 支持延迟加锁、提前解锁、转移所有权等灵活控制
D. `std::unique_lock` 不能与 `std::condition_variable` 配合使用

---

**解析：**

三层抽象：
- **`std::mutex`**：底层互斥量，手动 `lock()` / `unlock()`，容易忘记解锁。
- **`std::lock_guard`**：RAII 封装，构造时加锁，析构时解锁。不支持手动解锁、延迟加锁。
- **`std::unique_lock`**：更灵活的 RAII 封装，支持：延迟加锁（`std::defer_lock`）、尝试加锁（`try_lock`）、提前解锁（`unlock()`）、所有权转移（支持移动语义）。也是 `std::condition_variable::wait` 要求的锁类型。

**来源：** InterviewBit "C++ Interview Questions" — Mutex / lock_guard / unique_lock

## Explanation

正确答案是 C。
三层抽象： std::mutex：底层互斥量，手动 lock() / unlock()，容易忘记解锁；std::lock_guard：RAII 封装，构造时加锁，析构时解锁。
不支持手动解锁、延迟加锁；std::unique_lock：更灵活的 RAII 封装，支持：延迟加锁（std::defer_lock）、尝试加锁（try_lock）、提前解锁（unlock()）、所有权转移（支持移动语义）。
