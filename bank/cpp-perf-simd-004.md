---
qid: cpp-perf-simd-004
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要把 `std::vector<double>`（N=1M，正值，量级 1.0 左右）求和，要求**性能高且数值稳定**。下面四个写法功能等价（误差范围内），哪个最值得采用？

```cpp
// A
double s = 0.0;
for (double x : v) s += x;

// B
double s0=0, s1=0, s2=0, s3=0;
std::size_t i = 0;
for (; i + 4 <= v.size(); i += 4) {
    s0 += v[i];   s1 += v[i+1];
    s2 += v[i+2]; s3 += v[i+3];
}
double s = (s0 + s1) + (s2 + s3);
for (; i < v.size(); ++i) s += v[i];

// C
double s = std::reduce(std::execution::unseq, v.begin(), v.end(), 0.0);

// D
double s = 0.0, c = 0.0;
for (double x : v) {
    double y = x - c;
    double t = s + y;
    c = (t - s) - y;
    s = t;
}
```

A. A — 单累加器，朴素
B. B — 4 路并行累加器手写打破依赖链
C. C — std::reduce + unseq，标准库版本
D. D — Kahan 求和补偿算法，最精确

---

**解析：**

选 C。这道题考的是"性能 + 数值稳定性"的多目标权衡，要找到帕累托最优。

逐一品味：

- **A**：单累加器顺序求和。数值上 N=1M 量级 1.0 的 double 求和，最终累加值 ~1e6，相对误差 ~N·ε/2 ~ 1e6·1e-16 = 1e-10——还行但不是最佳。性能差（依赖链 + 无 SIMD）。**两边都不好**。
- **B**：4 路累加器**同时**改善了性能（打破依赖链，throughput ~4×）和数值稳定性（每个累加器只承担 N/4 项的累计误差，最终再加起来时数量级也不会爆炸——本质是 pairwise summation 的简化版）。手写但能 SIMD 化的实现。然而：**没有 `-ffast-math` 时编译器不一定能自动 SIMD**（因为程序员看似在做手工展开，但加法链顺序被钉死），且代码长。性能 ~A 的 4×，精度比 A 好。
- **C**：`std::reduce + unseq` 由标准库实现选择最优策略——libstdc++ 用 pairwise summation（分治结合），既向量化又数值稳定。**性能 ~A 的 8×**（向量宽度 + 多累加器），**精度比 A 高一个量级**（pairwise 的误差 O(log N · ε) 而非 O(N · ε)）。一行代码，标准，跨平台。是这道题的明确赢家。
- **D**：Kahan 求和 (compensated summation) **精度极佳**——误差 O(1)·ε，几乎不随 N 增长。但循环体内每次迭代有 4 个浮点运算 + 串行依赖链（`c` 和 `s` 都依赖前一次），**比 A 慢 3–4 倍**且**无法 SIMD**（依赖链太长）。仅当需要的精度连 pairwise 都不够时才用（如 N=1e9、量级跨多个数量级）。本题量级稳定的常规场景，C 已经足够。

C 是"标准库做了好事，用它"的典型——同时拿性能和稳定性，比手写都强。

**核心识别点：**
- 浮点求和 N>10⁴ → 警觉是不是该用 pairwise/Kahan 改善精度
- 单累加器顺序求和 → 性能（依赖链）和精度（O(N)·ε）都差
- pairwise/分治求和（B 的近似版，C 的标准库版）→ 同时拿性能和精度
- Kahan 是"补偿求和"，**精度好但慢**，不要默认用——只在精度真的关键时
- 标准库 `std::reduce` 在主流实现里就是 pairwise，免费拿到两个好处

**来源：** Higham, "Accuracy and Stability of Numerical Algorithms" 2nd ed., §4.2；C++17 P0024；BLAS DSDOT 实现注释；Goldberg, "What Every Computer Scientist Should Know About Floating-Point Arithmetic", ACM 1991.

## Explanation

选 C，因为 `std::reduce(std::execution::unseq, ...)` 同时给出重排和向量化许可，通常能采用多累加器或分治求和。它比单累加器更快也更稳定；Kahan 更精确但串行依赖强，适合极端精度需求而非本题的常规规模。误区是把“最精确”当成“最值得采用”，忽略性能与精度的权衡。
