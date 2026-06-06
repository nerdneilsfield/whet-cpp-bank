---
qid: cpp-perf-conc-001
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要在多个线程里共享一个计数器，每次只是 `+1`，最后读总数（顺序要求弱）。下面四个写法功能等价（在统计正确性意义上），哪个最值得采用？

```cpp
// A
std::atomic<long> counter{0};
// in each thread loop:
counter.fetch_add(1, std::memory_order_relaxed);

// B
long counter = 0;
std::mutex m;
// in each thread loop:
{ std::lock_guard lk(m); ++counter; }

// C
std::atomic<long> counter{0};
// in each thread loop:
counter.fetch_add(1, std::memory_order_seq_cst);

// D
std::atomic<long> counter{0};
// in each thread loop:
counter.fetch_add(1);  // 默认 memory_order_seq_cst
```

A. A — atomic + relaxed，不需要任何顺序保证
B. B — mutex 保护 + 普通自增，最直白
C. C — atomic + seq_cst，最强顺序保证
D. D — atomic 默认参数，相当于 C

---

**解析：**

选 A。这道题考的是"内存序的代价"——同样是原子操作，不同 memory order 在硬件层面差异巨大。

逐一品味：

- **A**：`fetch_add(1, relaxed)` 在 x86 上生成一条 `lock xadd` 指令——**仅保证原子性，不发任何内存屏障**。x86 本身的内存模型是 TSO（Total Store Order），普通 load/store 已经几乎顺序，relaxed 原子在 x86 上和 seq_cst 的指令**相同**（因为 lock 前缀本身就 implies 全屏障）；但在 ARM/POWER 等弱内存模型机器上**差异巨大**——relaxed 不需要 `dmb ish` 屏障，吞吐高 **2–10 倍**。语义上对"只是计数"足够。
- **B**：mutex 在无竞争时也要走 atomic CAS（acquire mutex）+ atomic store（release），加上若失败要 futex 系统调用进入内核等待。高竞争下吞吐崩溃。即使无竞争，每次 `++counter` 也是 ~30–100 ns；而 A 是 ~5–10 ns。**比 A 慢 5–20 倍**，且竞争下退化更严重（系统调用上下文切换 ~微秒级）。
- **C**：seq_cst 在 ARM 等弱模型上需要在原子操作前后插入完整的内存屏障 (`dmb ish`)，吞吐比 relaxed 低 2–10 倍。在 x86 上和 relaxed 生成的指令相同（因为 lock 已经够），代价等同。**ARM 上比 A 慢、x86 上等同 A**。但写代码时给出最强保证 = 默认承诺；除非真的需要其他线程能用这个计数器同步其他变量（cross-variable ordering），否则浪费。
- **D**：`fetch_add(1)` 默认参数就是 `seq_cst`——和 C 等价。陷阱：很多人写 `fetch_add(1)` 以为是"轻量的原子加"，**实际上是最强顺序**。在 ARM 上意外慢。

A 的核心是"用最弱的内存序满足需求"——计数器只需要每次 +1 是原子的，不需要让"在 +1 前发生的写"对其他线程可见，所以 relaxed 是正确选择。

**核心识别点：**
- 看见 `std::atomic<T>` 但不指定 memory_order → 警觉用了默认 seq_cst，跨平台可能慢
- 看见 mutex 保护一个**单变量自增** → 几乎一定能用 atomic 替换
- 内存序代价排序（弱→强）：relaxed < acquire/release < seq_cst
- x86 是 TSO，几乎所有原子操作的指令开销相同；ARM/POWER 弱模型下差异是 2–10 倍
- "计数器/统计/标志位"几乎都能用 relaxed；只有"用原子操作传递其他变量的可见性"才需要 acquire/release 或 seq_cst

**来源：** Anthony Williams, "C++ Concurrency in Action" 2nd ed., §5.3 "Synchronizing operations and enforcing ordering"；Herb Sutter, "atomic Weapons", C++ and Beyond 2012；Paul McKenney, "Memory Barriers: a Hardware View for Software Hackers".
