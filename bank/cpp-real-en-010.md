---
qid: cpp-real-en-010
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: C
tags: [interview-real, interviewbit]
---
`std::atomic` 和 `std::mutex` 分别应该在什么场景下使用？

A. `std::atomic` 可以替代所有 `std::mutex` 的使用场景
B. `std::mutex` 比 `std::atomic` 性能更好
C. 对简单变量（如计数器、标志位）用 `std::atomic` 无锁操作；对复杂临界区（多语句操作、多变量一致）用 `std::mutex`
D. 两者功能完全相同，只是语法不同

---

**解析：**

- **`std::atomic<T>`**：对 `T` 类型变量提供无锁的原子操作（硬件级别 CAS / LL-SC）。适用于共享计数器、标志位、简单状态变量。开销低，但只能操作单个变量。
- **`std::mutex`**：互斥锁保护临界区，可保护复杂操作（如同时更新多个相关变量）。涉及内核态切换（竞争时），开销高于 `atomic`。

选择原则：单变量原子操作 → `atomic`；多变量/复杂逻辑 → `mutex`。

**来源：** InterviewBit "C++ Interview Questions" — std::atomic vs std::mutex

## Explanation

正确答案是 C。
std::atomic<T>：对 T 类型变量提供无锁的原子操作（硬件级别 CAS / LL-SC）；适用于共享计数器、标志位、简单状态变量。
开销低，但只能操作单个变量；std::mutex：互斥锁保护临界区，可保护复杂操作（如同时更新多个相关变量）。
