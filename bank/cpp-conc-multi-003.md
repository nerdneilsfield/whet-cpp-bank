---
qid: cpp-conc-multi-003
type: multi
kp: [cpp-concurrency]
difficulty: medium
answer_key: [A, B, D]
---
关于 C++ 标准库的互斥量类型，**哪些说法是正确的**？（多选）

A. `std::mutex` 不可递归，同一线程重复加锁会导致死锁或 UB。
B. `std::recursive_mutex` 允许同一线程多次加锁，必须解锁相同次数。
C. `std::shared_mutex` 只允许一个线程同时持有共享锁。
D. `std::timed_mutex` 支持带超时的 `try_lock_for` / `try_lock_until`。

---

**解析：**

A 正确：非递归互斥量不可由同一线程重复加锁。
B 正确：递归互斥量必须匹配加锁/解锁次数。
C 错误：`shared_mutex` 允许多个线程同时持有共享（读）锁，独占（写）锁排他。
D 正确：`timed_mutex` 提供带超时的尝试加锁接口。