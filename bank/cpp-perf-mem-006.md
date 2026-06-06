---
qid: cpp-perf-mem-006
type: single
kp: [cpp-arrays-pointers, cpp-algorithms]
primary_kp: cpp-arrays-pointers
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要在一个 `std::vector<Node>`（每个 Node 64 字节）上按 `indices[i]` 给出的随机顺序读 N=1M 个节点的 `value` 字段求和。下面四种写法功能相同，哪个最值得采用？

```cpp
// A
long s = 0;
for (std::size_t i = 0; i < N; ++i)
    s += nodes[indices[i]].value;

// B
constexpr int D = 8;
long s = 0;
for (std::size_t i = 0; i < N; ++i) {
    if (i + D < N)
        __builtin_prefetch(&nodes[indices[i + D]], 0, 0);
    s += nodes[indices[i]].value;
}

// C
std::vector<std::size_t> sorted_idx(indices, indices + N);
std::sort(sorted_idx.begin(), sorted_idx.end());
long s = 0;
for (auto k : sorted_idx) s += nodes[k].value;

// D
long s = 0;
#pragma GCC ivdep
for (std::size_t i = 0; i < N; ++i)
    s += nodes[indices[i]].value;
```

A. A — 直接按 indices 顺序访问，最简单
B. B — 提前 8 步预取下一个要用的节点
C. C — 排序后再访问，访问顺序变成升序
D. D — 加一条 ivdep 暗示告诉编译器循环无依赖

---

**解析：**

选 C。这道题考的是"硬件预取器只对顺序流有用，对随机访问唯一的救星是把顺序变回来"。

逐一品味：

- **A**：完全随机访问 1M 节点，每个 64B。N=1M × 64B = 64 MB，远超 L3。每次访问几乎必走 DRAM，**~200 cycles/访问**，吞吐 = 频率/200。这是基线，慢。
- **B**：手工预取看似聪明，但有两个根本限制：① `nodes[indices[i+D]]` 需要先读 `indices[i+D]`——这个 load 本身就有依赖延迟；② 预取距离 D 是猜的，D 太小覆盖不到 DRAM 延迟，D 太大塞爆 LFB（Line Fill Buffer，典型 10–12 项）；③ 软件预取占用 TLB/load port 资源，常常被硬件预取器自己挡掉。实测对"随机但有 hint"的场景能拿到 **1.5–2×**，但和 C 比仍差几倍。
- **C**：先排序索引（O(N log N) ~30M comparisons，~30 ms），后续访问变成对 `nodes` 的顺序扫描——硬件预取器立刻识别出步长模式，每条 cache line 抓一次但能用 8 个 int64 字段（如果只读 value），更重要的是**预取器把 DRAM 延迟完全隐藏**。访问总时间从 ~200ms（A）降到 ~20ms。即使加上排序开销，整体仍比 A 快 **3–5 倍**。这就是 Carruth/Acton 一再强调的"先 sort 再 traverse"模式。
- **D**：`ivdep` 告诉编译器忽略向量化的数据依赖检查，对纯随机访问 + 求和**没用**——瓶颈在内存延迟而非编译器无法向量化。Pragma 改不了硬件层面的 cache miss。

**核心识别点：**
- 看见"按外部给的索引数组随机访问大数组" → 警觉是不是 random-access scatter/gather，预取器全瞎
- 看见 `__builtin_prefetch` → 警觉是不是在用软件预取掩盖根本性的访问模式问题
- 看见 `#pragma` 暗示 → 几乎都解决不了内存延迟问题
- 排序索引把随机访问转成顺序访问，是 DOD 的标准武器："访问模式重要于代码漂亮"

**来源：** Mike Acton, "Data-Oriented Design", CppCon 2014；Drepper, "What Every Programmer Should Know About Memory", §6.3 "Prefetching"；Chandler Carruth, "Tuning C++: Benchmarks, and CPUs, and Compilers!", CppCon 2015.

## Explanation

选 C，因为随机索引访问大数组的瓶颈是 DRAM 延迟和预取失败。先排序索引把访问变成近似顺序流，硬件预取器和 cache line 利用率都会明显改善，即使付出排序成本也常更快。误区是指望 `ivdep` 或小距离软件预取解决根本随机访问模式。
