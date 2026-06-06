---
qid: cpp-conc-adv-013
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

`std::memory_order_relaxed` 的特性是？

A. 保证原子性，且保证该操作前后的内存访问不会被重排
B. 仅保证操作本身的原子性，不提供任何跨线程的顺序保证，不适合用于同步
C. 等价于 `memory_order_seq_cst`，只是性能更好
D. 只能用于读操作（load），不能用于写操作（store）
