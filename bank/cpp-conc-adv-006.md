---
qid: cpp-conc-adv-006
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

使用 `std::call_once` 实现线程安全单例，相比手写双重检查锁（double-checked locking）的优势是？

A. `std::call_once` 由标准库保证正确性，手写双重检查锁在某些内存序下存在数据竞争风险
B. `std::call_once` 性能更高，因为不使用任何同步原语
C. 手写双重检查锁更安全，`std::call_once` 存在已知竞态条件
D. 两者等价，只是写法不同，没有安全性差异
