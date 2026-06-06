---
qid: cpp-perf-mem-008
type: single
kp: [cpp-algorithms, cpp-arrays-pointers]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要把 `double A[N][N]`（N=2048）转置到 `B[N][N]`，使 `B[j][i] = A[i][j]`。下面四个写法功能相同，哪个最值得采用？

```cpp
// A
for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        B[j][i] = A[i][j];

// B
for (int j = 0; j < N; ++j)
    for (int i = 0; i < N; ++i)
        B[j][i] = A[i][j];

// C
constexpr int T = 32;
for (int ii = 0; ii < N; ii += T)
    for (int jj = 0; jj < N; jj += T)
        for (int i = ii; i < ii + T; ++i)
            for (int j = jj; j < jj + T; ++j)
                B[j][i] = A[i][j];

// D
#pragma GCC ivdep
for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
        B[j][i] = A[i][j];
```

A. A — 按 A 的行序遍历，A 端顺序访问，最自然
B. B — 按 B 的行序遍历，B 端顺序访问，对称的另一半
C. C — 把矩阵切成 32×32 的小块，先做完一块再换块
D. D — 在 A 上加 ivdep 告诉编译器循环可向量化

---

**解析：**

选 C。这道题考的是"转置注定有一端要跨行访问，唯一的优化是让跨行的距离落进 cache"。

逐一品味：

- **A**：内层 `j` 走完 A 的一行（顺序、cache 友好），但同时往 B 写——`B[j][i]` 内层 j 变化意味着每次写**跨 N×8B = 16KB**，L1 (32KB) 装不下连续多次的写。N=2048 时写端基本每次都 miss。L1 写端 miss 主导整体时间。
- **B**：和 A 完全对称——把读端变成跨行 miss、写端变成顺序。**总 cache miss 数和 A 几乎一样**，因为无论哪种顺序都有一端跨行。看起来"换了方向就改善"是错觉。
- **C**：分块（tiling，又叫 cache blocking）。32×32 的小块大小 = 32×32×8B = **8 KB**，A 的一块和 B 的一块（各 8 KB）合起来 16 KB，舒服塞进 L1 (32KB)。内层两个循环只在一块内部访问，读写两端**全部 L1 命中**。块间切换的 cache miss 数从 N² 降到 N²/T。实测对 2048×2048 矩阵比 A/B 快 **3–8 倍**，是 Goto/BLAS、FFTW、GEMM 库的核心模式。
- **D**：`ivdep` 提示编译器忽略依赖检查以便向量化，但**转置的瓶颈是 cache miss 不是向量化**——单条 store 指令也撑不满内存带宽。即使编译器愿意向量化，scatter store 在 AVX-512 之前性能也很差。Pragma 没用对地方。

**核心识别点：**
- 看见"读和写两端的访问步长冲突"（一个顺序、一个跨行）→ 警觉分块是不是必需
- 看见暴力两重循环操作 N≥1024 的矩阵 → 想想"小块能不能塞进 L1（32KB）"
- 看见 `#pragma ivdep`/`#pragma omp simd` → 警觉是不是误以为向量化能修 cache 问题
- L1 ~32KB、L2 ~256KB、L3 ~MB 级——选 tile 大小要让"两端工作集"加起来塞进目标 cache
- 分块是缓存敏感算法（GEMM、卷积、转置、FFT）的通用武器

**来源：** Goto & van de Geijn, "Anatomy of High-Performance Matrix Multiplication", ACM TOMS 2008；Drepper, "What Every Programmer Should Know About Memory", §6.2.1；Intel Optimization Reference Manual, §11.6 "Tiling".
