---
qid: cpp-perf-mem-005
type: single
kp: [cpp-concurrency, cpp-classes]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: D
tags: [performance, code-taste]
---

两个线程各自疯狂自增一个独立的计数器。下面四种放法功能等价，哪个最值得采用？

```cpp
// A
struct Counters {
    std::atomic<long> a{0};
    std::atomic<long> b{0};
};
Counters c;
// thread 1: for (...) c.a.fetch_add(1, std::memory_order_relaxed);
// thread 2: for (...) c.b.fetch_add(1, std::memory_order_relaxed);

// B
struct Counters {
    std::atomic<long> a{0};
    char pad[8];
    std::atomic<long> b{0};
};
Counters c;

// C
struct Counters {
    std::atomic<long> a{0};
    std::atomic<long> b{0};
};
Counters* c1 = new Counters();
Counters* c2 = new Counters();
// thread 1 用 c1->a, thread 2 用 c2->b

// D
struct Counters {
    alignas(64) std::atomic<long> a{0};
    alignas(64) std::atomic<long> b{0};
};
Counters c;
```

A. A — 两个 atomic 紧挨着，最紧凑
B. B — 中间垫 8 字节，把两个变量分开
C. C — 两个 Counters 各自堆分配，地址离得远
D. D — 每个变量都用 alignas(64) 单独占满一条 cache line

---

**解析：**

选 D。这道题考的是"两个独立 atomic 在同一条 cache line 上，会被 MESI 协议拖到几乎像加了锁"。

逐一品味：

- **A**：`a` 和 `b` 各 8 字节，紧挨在结构体里，几乎肯定落在**同一条 64B cache line**。线程 1 写 `a` 时，硬件 cache 一致性协议（MESI）必须把这条 line 在另一个核的 cache 里设为 invalid；线程 2 紧接着写 `b` 又把 line 拉到自己核且 invalidate 线程 1 的副本。两个本来独立的变量被 line 绑定，每次写都触发跨核 ping-pong。实测吞吐比 D 慢 **20–100 倍**——这就是经典 false sharing。
- **B**：垫了 8 字节但**总大小才 24 字节**，`b` 仍在同一条 cache line 内（line 边界是 64B 倍数）。完全没有解决问题，看起来"分开了"实际还是一样慢。这是最容易写错的"修补"。
- **C**：两个 Counters 堆分配，地址被分配器随机化，常常落到不同 line。但 **`Counters` 内部** `a` 和 `b` 仍紧挨着——线程 1 用 `c1->a` 时，`c1->b` 也被 invalidate 占用了 line 的另一半；若程序里别处碰 `c1->b`，依然有 false sharing。这种"只把外层分开、内层没分"是常见的伪修复。
- **D**：`alignas(64)` 强制每个 atomic 起始在 cache line 边界，且 `sizeof(Counters) = 128`，`a` 和 `b` 各占一条独立 line。两个线程写各自 line，MESI 协议互不打扰，吞吐基本等于单线程独占。这是 C++17 引入 `std::hardware_destructive_interference_size` 想标准化的同一件事。

**核心识别点：**
- 看见多线程各写一个变量但仍很慢 → 警觉两个变量是不是共住一条 64B line（false sharing）
- 看见用 `char pad[8]`/`char pad[16]` 这种小垫片 → 几乎肯定垫不够，64B 才是边界
- `alignas(64)` 或 `alignas(std::hardware_destructive_interference_size)` 是修 false sharing 的正确姿势
- 一个 atomic 本身不慢，但跨核被反复 invalidate 的代价是 ~100 cycles 一次

**来源：** Intel Optimization Reference Manual, §11.10 "False Sharing"；Herb Sutter, "Eliminate False Sharing", Dr. Dobb's；C++17 `std::hardware_destructive_interference_size` 提案（P0154）；Anthony Williams, "C++ Concurrency in Action" 2nd ed., §8.2.
