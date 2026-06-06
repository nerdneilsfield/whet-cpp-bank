---
qid: cpp-perf-branch-006
type: single
kp: [cpp-control-flow, cpp-algorithms]
primary_kp: cpp-control-flow
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要把 `double a[N]` 求和到 `s`，N=1M 且在编译期不知。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
double s = 0;
for (std::size_t i = 0; i < n; ++i)
    s += a[i];

// B
double s = 0;
std::size_t i = 0;
for (; i + 4 <= n; i += 4) {
    s += a[i];
    s += a[i+1];
    s += a[i+2];
    s += a[i+3];
}
for (; i < n; ++i) s += a[i];

// C
double s = 0;
#pragma unroll 8
for (std::size_t i = 0; i < n; ++i)
    s += a[i];

// D
double s0=0, s1=0, s2=0, s3=0;
std::size_t i = 0;
for (; i + 4 <= n; i += 4) {
    s0 += a[i];
    s1 += a[i+1];
    s2 += a[i+2];
    s3 += a[i+3];
}
double s = s0 + s1 + s2 + s3;
for (; i < n; ++i) s += a[i];
```

A. A — 朴素 for 循环，把展开/向量化完全交给编译器
B. B — 手工 4 路展开循环体
C. C — 用 #pragma unroll 8 暗示编译器展开 8 次
D. D — 用 4 个独立累加器打破浮点加法依赖链

---

**解析：**

选 A。这道题考的是"编译器能做的事，手写常常做得更差"。

逐一品味：

- **A**：现代编译器（GCC 12+/Clang 14+，`-O2`/`-O3`）看到简单求和循环时会做：① 自动展开 4–8 次；② 自动开多累加器（因为 `-ffast-math` 或者识别到 reduction 模式时，标准库 `std::accumulate` 也类似）；③ 自动向量化到 AVX2 (4× double) 或 AVX-512 (8× double)；④ 循环结尾自动补 scalar epilogue。最终生成的代码几乎等同于 D 的向量化版本，**还更鲁棒**（处理任意 N、对齐情况）。
- **B**：手工展开但**只用一个累加器 s**——`s += a[i]; s += a[i+1]; ...` 全部串成一条 RAW 依赖链。FP 加法在主流 CPU 上**延迟 ~4 cycles、throughput 0.5/cycle**。串行链让 throughput 退化到延迟主导：每 4 cycles 才能完成一次加。展开了形式，没有打破依赖链——**比 A 还慢**（因为编译器对原始循环可能更易识别 reduction 模式而开多累加器，手工版反而打消了这种识别）。
- **C**：`#pragma unroll` 是 Clang/ICC 扩展，告诉编译器物理展开。但**展开本身没用**——重点是打破依赖链。如果编译器看到展开后仍是 `s += ...; s += ...;` 链，只能展开但不能并行。在 `-ffast-math` 下编译器才敢自己做累加器重排。所以效果常常等同 B 或仅略好。
- **D**：4 个独立累加器，**打破了浮点依赖链**——4 条加法链可以同时执行，throughput 翻 4 倍。配合 SIMD 后能跑到内存带宽极限。性能上和 A 在 `-O3 -ffast-math` 下几乎一样（编译器自己也会做这个），但**手写引入了精度差异**（浮点加法不结合，分组求和的尾数不同），且若编译器选项不同（如 `-O2` 默认禁 reassoc）反而比 A 跑得慢。

A 在现代编译器下是最好的选择：① 代码简洁；② 自动跟随编译器/架构升级（AVX-512、SVE）；③ 编译器在 `-ffast-math` 下会做 D 的优化，且更彻底（向量寄存器内多累加器）。手写优化反而锁死了能达到的上限。

**核心识别点：**
- 看见手写循环展开 → 警觉是不是在做编译器已经会做的事，且可能做得更差
- 看见手写多累加器 → 思考是否是为了打破 FP 依赖链；若为打破依赖链，依赖编译器 `-ffast-math` 是不是更干净
- `#pragma unroll` 单独使用几乎无效，必须配合打破依赖链
- 现代编译器在 `-O3` 下做的展开/向量化/累加器重排往往超过人手写
- 手写优化的隐性成本：精度变化、跨编译器行为差异、阻碍未来的更好优化

**来源：** Chandler Carruth, "Tuning C++: Benchmarks, and CPUs, and Compilers!", CppCon 2015；Agner Fog, "Optimizing software in C++", §8.3 "Loop unrolling"；Intel Optimization Reference Manual, §3.5.2.1 "Loop Unrolling".

## Explanation

这题关注短路逻辑与条件顺序：应先判断便宜且更可能排除的条件，让常见路径尽早结束。条件顺序不只是可读性问题，也影响分支预测、加载次数和异常路径是否进入热循环。误区是把布尔表达式视为数学交换律，忘了 C++ 的短路求值有执行顺序和性能后果。
