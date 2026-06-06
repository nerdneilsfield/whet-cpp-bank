---
qid: cpp-perf-mem-002
type: single
kp: [cpp-arrays-pointers, cpp-control-flow]
primary_kp: cpp-arrays-pointers
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要把 `double m[N][N]`（N=4096）里的所有元素加 1。下面四个写法功能相同，哪个最值得采用？

```cpp
// A
for (std::size_t i = 0; i < N; ++i)
    for (std::size_t j = 0; j < N; ++j)
        m[i][j] += 1.0;

// B
for (std::size_t j = 0; j < N; ++j)
    for (std::size_t i = 0; i < N; ++i)
        m[i][j] += 1.0;

// C
for (std::size_t k = 0; k < N * N; ++k) {
    std::size_t i = k / N, j = k % N;
    m[i][j] += 1.0;
}

// D
std::vector<std::pair<std::size_t,std::size_t>> idx;
idx.reserve(N * N);
for (std::size_t i = 0; i < N; ++i)
    for (std::size_t j = 0; j < N; ++j)
        idx.emplace_back(i, j);
for (auto [i, j] : idx) m[i][j] += 1.0;
```

A. A — 外 i 内 j，最自然的二重循环
B. B — 外 j 内 i，对称写法，编译器一样能优化
C. C — 把二重循环展平成单循环，给编译器更多自由
D. D — 提前算好所有下标存起来，循环体里没分支

---

**解析：**

选 A。这道题考的是"硬件按行存的二维数组，循环顺序错了就要付几十倍代价"。

逐一品味：

- **A**：内层 `j` 走完一行才换 `i`，访问地址 `&m[i][0], &m[i][1], ...` 完全顺序。每条 cache line 装 8 个 double，每 8 次访问只触发一次 cache miss，**命中率 87.5%**。硬件流式预取器一眼识别出模式，提前把下一行抓上来，DRAM 延迟被隐藏。自动向量化也能展开成 4–8 路 SIMD。
- **B**：内层 `i` 一动就跨 N×sizeof(double) = 32 KB，**每次访问都触发新 cache line**——N=4096 时，每个内循环迭代都是 L1/L2/L3 全 miss，走到 DRAM ~200 cycles。整体比 A 慢 **10–50 倍**，是矩阵代码里最经典的"行列搞反"。
- **C**：表面上"展平"，但 `k / N` 和 `k % N` 在每次迭代里要做整数除法和取模，整数除法在 x86 上是 ~20+ cycles 的高延迟指令，破坏流水线。即便编译器把它优化成位运算（N 是 2 的幂时），访问顺序和 A 一样但额外引入了下标计算的依赖链，最终略慢于 A，**没有任何收益**。
- **D**：先建一个 16M 项的 `pair` vector（256 MB 额外内存），再二次遍历。第一遍写完那 256 MB 已经把 L3 全冲掉，第二遍访问 `m` 时连续性虽然保留，但多了**一倍的内存流量**和巨大的额外分配。比 A 慢 **3–8 倍**，还吃光内存。

**核心识别点：**
- 看见嵌套循环访问 `m[i][j]` → 第一反应是确认内层 index 对应内存里相邻字节
- 看见"展平、缓存下标、提前计算"等"重写循环"的花活 → 警觉是不是把简单的顺序访问搞复杂了
- 整数除法/取模在热点循环里几乎都是反模式
- 一条 64B cache line 装 8 个 double：内层迭代步长是 8B 就 100% 利用，是 32KB 就 0%

**来源：** Drepper, "What Every Programmer Should Know About Memory", §3.3；Intel Optimization Reference Manual, §3.6 "Prefetching"；Hennessy & Patterson, "Computer Architecture: A Quantitative Approach", §2.3.
