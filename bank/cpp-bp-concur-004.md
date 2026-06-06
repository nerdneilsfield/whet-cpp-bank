---
qid: cpp-bp-concur-004
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

下面的"高性能"计数器在多线程环境下性能极差，原因是？

```cpp
struct alignas(8) Counter {
    std::atomic<uint64_t> total{0};
    std::atomic<uint64_t> errors{0};
    std::atomic<uint64_t> bytes{0};
    std::atomic<uint64_t> requests{0};
};

Counter g_counter;

// 8 个线程各自只 increment 一个字段
void thread_total()    { g_counter.total++; }
void thread_errors()   { g_counter.errors++; }
void thread_bytes()    { g_counter.bytes++; }
void thread_requests() { g_counter.requests++; }
```

A. atomic 本身就慢
B. false sharing：4 个字段共享同一 cache line（64B），不同线程修改不同字段时 cache line 在 CPU 间反复 invalidate
C. uint64_t 在 32-bit 上不是原子的
D. 应该用 std::mutex 替换 std::atomic

---

**解析：**

**False sharing（伪共享）** 是多核性能最常见的陷阱。

CPU 的最小内存一致性单元是 **cache line（典型 64 字节）**。当多个核心修改同一 cache line 内的**不同字节**时，硬件按 MESI 协议 invalidate 其他核的副本，迫使每次修改都从其他核拉取最新数据 → 性能跌到与"锁竞争"等同。

`Counter` 4 个 8 字节字段共 32 字节，全部塞在同一 cache line 内。即使每个字段被不同线程独占修改，**4 个字段在硬件层面相当于争抢同一资源**，性能可下降 10-100 倍。

解决方法——**cache line 对齐 + padding**：

```cpp
struct alignas(64) Counter {                      // C++17
    alignas(64) std::atomic<uint64_t> total{0};
    alignas(64) std::atomic<uint64_t> errors{0};
    alignas(64) std::atomic<uint64_t> bytes{0};
    alignas(64) std::atomic<uint64_t> requests{0};
};
// sizeof(Counter) 现在是 256B，每个字段独占 1 个 cache line
```

C++17 提供了标准化的 cache line 常量：

```cpp
#include <new>
struct Counter {
    alignas(std::hardware_destructive_interference_size) std::atomic<uint64_t> total{0};
    alignas(std::hardware_destructive_interference_size) std::atomic<uint64_t> errors{0};
    // ...
};
```

`std::hardware_destructive_interference_size` 通常是 64 或 128（Apple Silicon 是 128）。

诊断工具：`perf c2c`（Cache-to-Cache）可以直接定位 false sharing 热点。