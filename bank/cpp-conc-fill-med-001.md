---
qid: cpp-conc-fill-med-001
type: fill
kp: [cpp-concurrency]
difficulty: medium
answer_key: "lock_guard"
---
RAII 包装互斥锁的最简类是 `std::___`。

---

**解析：**

`std::lock_guard` 是 `<mutex>` 中最简单的 RAII 互斥锁包装类：构造时锁定互斥量，析构时自动解锁。它不支持手动加解锁或条件变量等待，适用于简单的作用域保护场景。`std::unique_lock` 则提供更灵活的所有权管理（可移动、延迟锁定、提前解锁等）。