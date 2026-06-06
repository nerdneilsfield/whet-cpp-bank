---
qid: cpp-real-nk-032
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: A
tags: [interview-real, bytedance]
---

下列 C++ 互斥量管理方式中，**支持 defer_lock（延迟锁定）且支持可移动**的是：

```cpp
// 类型 1: X
// 类型 2: Y
// 类型 3: Z
```

A. X = `std::unique_lock`, Y = `std::lock_guard`, Z = `std::scoped_lock`
B. **X = `std::unique_lock`**（支持 defer_lock / 可移动 / 手动 unlock）；`lock_guard` 和 `scoped_lock` 不支持 defer_lock
C. 只有 `std::lock_guard` 支持 defer_lock
D. 三者都支持 defer_lock

---

**解析：**

三种锁对比：

| 特性 | lock_guard | unique_lock | scoped_lock (C++17) |
|------|-----------|-------------|-------------------|
| 构造时锁定 | ✅ | ✅ | ✅ |
| defer_lock | ❌ | ✅ | ❌ |
| try_lock | ❌ | ✅ | ❌ |
| 手动 unlock | ❌ | ✅ | ❌ |
| 可移动 | ❌ | ✅ | ❌ |
| 锁定多个 mutex | ❌ | ❌ | ✅（死锁避免） |

**lock_guard**：最简单的 RAII 包装，构造加锁析构解锁，不可扩展。

**unique_lock**：最灵活，支持延迟锁定、try_lock、手动 unlock（需要与 condition_variable 配合）、可移动（unique_lock 可以作为函数返回值）。

**scoped_lock**：C++17 引入，目的就是解决 lock_guard 不能同时锁多个 mutex 的问题（`lock(m1, m2)` 不会被死锁的算法）。

**来源：** 字节并发面试题 / cppreference