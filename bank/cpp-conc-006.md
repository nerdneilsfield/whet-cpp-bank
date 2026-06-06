---
qid: cpp-conc-006
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "unique_lock"
---

# 认知：可手动解锁的锁

`std::lock_guard` 不支持手动 `unlock()`，若需要在持锁期间提前释放锁，应改用 `std::____`。
