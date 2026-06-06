---
qid: cpp-perf-conc-002
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: D
tags: [performance, code-taste]
---

要保护一个 hash map 的并发访问，每次操作是**约 200–500 ns 的查找/插入**（不太短也不太长），16 个线程争用。下面四种同步方案功能等价，哪个最值得采用？

```cpp
// A
std::atomic_flag lock = ATOMIC_FLAG_INIT;
// 操作: while (lock.test_and_set(std::memory_order_acquire)) {}
//      do_op();
//      lock.clear(std::memory_order_release);

// B
class SpinLock {
    std::atomic<bool> locked{false};
public:
    void lock()   { while (locked.exchange(true, std::memory_order_acquire)); }
    void unlock() { locked.store(false, std::memory_order_release); }
};
SpinLock sl;
// 操作: sl.lock(); do_op(); sl.unlock();

// C
class BackoffSpinLock {
    std::atomic<bool> locked{false};
public:
    void lock() {
        while (locked.exchange(true, std::memory_order_acquire)) {
            while (locked.load(std::memory_order_relaxed)) _mm_pause();
        }
    }
    void unlock() { locked.store(false, std::memory_order_release); }
};
BackoffSpinLock sl;

// D
std::mutex m;
// 操作: { std::lock_guard lk(m); do_op(); }
```

A. A — 用 atomic_flag，标准库提供的"最简自旋锁"
B. B — 自己写 bool 自旋锁，朴素
C. C — 自旋锁加 pause + test-and-test-and-set
D. D — std::mutex，让 OS/libstdc++ 处理

---

**解析：**

选 D。这道题考的是"自旋锁 vs mutex 的临界区长度阈值"——临界区不那么短时，mutex 更优。

逐一品味：

- **A**：`atomic_flag` 的 `test_and_set` 在循环里被高频调用，**每次都是 atomic RMW**——在多核上每次 RMW 都让 cache line 在核间 ping-pong，吞吐崩溃。16 个线程同时争用时，这个锁会让总吞吐反而比单线程更低（"反向加速"）。且无 backoff，纯忙等待会把 SMT sibling 核挤死、温度墙拉满频率降低。
- **B**：和 A 本质一样——`exchange(true)` 也是高频 RMW，每次让 line 在核间反弹。**比 A 略好**（只在抢锁时 RMW，但 A 的 `test_and_set` 不释放时也只是一次 RMW），实际差不多。无 backoff，竞争下糟糕。
- **C**：经典的 *test-and-test-and-set + pause* 模式：先用 relaxed load 等待 line 变 free（**只读不写，line 可在各核保留共享状态**，不触发 invalidate），看见 free 才尝试 RMW 抢锁。`_mm_pause`（x86 PAUSE 指令）暗示 CPU "我在忙等，给 SMT sibling 让让资源"。这是高质量自旋锁的形态——**但只适合临界区 <100 ns 的极短场景**。本题临界区 200–500 ns，多线程争用时仍有数百 ns 的忙等浪费，且**长时间忙等不释放 CPU**，调度公平性差、能耗高。
- **D**：`std::mutex` 在 Linux 上典型实现是 futex：先**用户态 try-lock**（一次 atomic CAS，~10 ns），失败再 futex 系统调用让线程进入 sleep（~微秒级 syscall），由内核在 unlock 时唤醒。优势：① 无竞争时几乎和自旋锁一样快（一次 atomic）；② 高竞争时**线程 sleep 而非燃烧 CPU**——CPU 资源还给其他线程；③ 公平性由 OS 调度保证。临界区 200–500 ns + 16 线程争用下，自旋锁全员忙等 1500 ns 累积浪费 CPU，mutex 让大部分线程睡眠等待，**整体吞吐高 30–100%**。

自旋锁仅在两个条件都满足时优于 mutex：① 临界区极短（< ~50–100 ns）；② 线程数 ≤ 物理核数（不会让自旋者把锁持有者挤出 CPU）。本题不满足，应用 mutex。

**核心识别点：**
- 看见手写自旋锁 → 警觉是不是临界区其实没那么短，反而 mutex 更优
- 看见自旋锁缺 `_mm_pause()`/`__builtin_ia32_pause()` → 警觉浪费 SMT 资源、温度墙
- 看见 atomic flag/exchange 在 hot path 的 spin → 警觉 cache line ping-pong，应改 test-and-test-and-set
- 临界区时间阈值：< 50 ns 自旋；50 ns – 几 μs 视争用决定；> 几 μs 一定 mutex
- 现代 `std::mutex` 的 futex 实现：无竞争 ≈ 自旋锁，有竞争自动 sleep，不要怕用

**来源：** Anthony Williams, "C++ Concurrency in Action" 2nd ed., §5.4；Intel Optimization Reference Manual, §11.4.2 "Spin-wait Loops"；Ulrich Drepper, "Futexes Are Tricky"；Paul McKenney, "Is Parallel Programming Hard, And, If So, What Can You Do About It?", §6.
