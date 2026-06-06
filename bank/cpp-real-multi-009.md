---
qid: cpp-real-multi-009
type: multi
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: [A, B, D]
tags: [interview-real, multi-vendor]
---
```cpp
std::mutex m;
std::mutex m2;

// 选项 1: lock_guard
{ std::lock_guard<std::mutex> lk(m); /* ... */ }

// 选项 2: unique_lock
{ std::unique_lock<std::mutex> lk(m, std::defer_lock);
  lk.lock(); /* 灵活 */ lk.unlock(); }

// 选项 3: scoped_lock (C++17)
{ std::scoped_lock lk(m, m2); /* 多锁，无死锁 */ }
```
关于 `std::mutex` 系列辅助类的选择，以下说法**正确**的是（多选）：

A. `lock_guard` 是最轻量的 RAII 锁，构造时上锁、析构时解锁，不能解锁后再上锁
B. `unique_lock` 比 `lock_guard` 灵活，支持延迟锁、转移所有权、条件变量配合，但开销稍大
C. `scoped_lock` 可同时获取多个锁，但**仍可能死锁**，需用户自行设计锁顺序
D. `scoped_lock`（C++17）用 deadlock-avoidance 算法（类似 std::lock）一次性获取多个锁，自动避免死锁
E. 条件变量 `condition_variable::wait` 可以配合 `lock_guard` 使用

---

**解析：**

正确答案：**A、B、D**。

**四种锁辅助类对比：**

| 类 | 引入版本 | 特性 | 适用场景 |
|---|---|---|---|
| `lock_guard` | C++11 | 构造锁，析构解锁，无其他操作 | 简单临界区 |
| `unique_lock` | C++11 | 支持 defer/try/timed lock、unlock/relock、所有权转移 | 条件变量、复杂控制 |
| `scoped_lock` | C++17 | 类似 lock_guard 但支持多锁，自动避免死锁 | 多锁场景 |
| `shared_lock` | C++14 | 配合 `shared_mutex` 做共享（读）锁 | 读多写少 |

**A 正确：** lock_guard 是"哑铃式"——构造-上锁，析构-解锁。**没有 unlock 方法**，不能中途释放。

**B 正确：** unique_lock 灵活功能：
```cpp
std::unique_lock<std::mutex> lk(m, std::defer_lock);  // 不立即上锁
lk.lock();          // 手动上锁
lk.unlock();        // 手动解锁
lk.try_lock();      // 非阻塞尝试
auto lk2 = std::move(lk);  // 转移所有权（lock_guard 不行）
cv.wait(lk);        // 配合 condition_variable
```
开销略大（多一个 bool 标记锁状态）。

**C 错误（D 正确）：** scoped_lock **能避免死锁**。它使用 `std::lock(m1, m2, ...)` 算法（类似 try_lock + back-off 重试），保证不会死锁。这是 scoped_lock 的关键价值。

**E 错误：** `condition_variable::wait` 要求传入 `std::unique_lock<std::mutex>`（不是 lock_guard），因为 wait 内部需要 unlock + 等待 + relock，需要 unique_lock 的能力。`condition_variable_any` 可以配合任意 BasicLockable，但标准 cv 必须用 unique_lock。

**总结：**
- 一般用 lock_guard（最快）
- 配合 cv 或需要灵活控制 → unique_lock
- 多个锁 → scoped_lock（C++17）或 std::lock + lock_guard（C++11）

**来源：** 跨厂 C++ 并发面试常考（参考：cppreference、《C++ Concurrency in Action》第 3 章）