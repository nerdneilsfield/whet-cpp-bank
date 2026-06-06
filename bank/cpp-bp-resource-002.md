---
qid: cpp-bp-resource-002
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: D
---

下列锁守卫的选择，哪个**最不合理**？

```cpp
std::mutex m1, m2;
std::shared_mutex rw;
std::condition_variable cv;

// A：保护短临界区，编译期已知 1 个 mutex
void inc() {
    std::lock_guard lk(m1);
    counter++;
}

// B：需要在 cv.wait 中释放并重新获取
void consumer() {
    std::unique_lock lk(m1);
    cv.wait(lk, []{ return ready; });
}

// C：同时加多个锁，避免死锁
void transfer() {
    std::scoped_lock lk(m1, m2);   // C++17
}

// D：纯读多线程，写线程极少
void read() {
    std::lock_guard lk(rw);        // ← 这里
    return data;
}
```

A. A
B. B
C. C
D. D

---

**解析：**

各锁守卫的选择标准：

- `std::lock_guard`：最轻、最简单，仅支持 RAII 加/解锁，**不能释放或重锁**。短临界区首选。
- `std::unique_lock`：可以 unlock/lock、可配合 cv.wait（必须）、可移动。**比 lock_guard 重**（多一 bool 跟踪状态）。
- `std::scoped_lock`（C++17）：同时锁多个 mutex 时自动避免死锁（用 std::lock 的算法），单 mutex 时等价于 lock_guard。
- `std::shared_mutex` + `std::shared_lock`：读多写少时允许多读者并发。

选项 D 是**典型错误**：拿 `std::shared_mutex` 用 `lock_guard` 加锁是加**写锁**（独占锁），完全失去 shared_mutex 的并发读优势，比直接用 `std::mutex` 还要慢（shared_mutex 本身实现更重）。

正确做法：
```cpp
// 读：共享锁
void read() {
    std::shared_lock lk(rw);
    return data;
}
// 写：独占锁
void write(T x) {
    std::unique_lock lk(rw);  // 或 std::lock_guard
    data = x;
}
```

附：shared_mutex 只在**读 >> 写 且临界区长**时才值得，否则 plain mutex 通常更快（无写者饥饿、cache line 竞争少）。