---
qid: cpp-perf-simd-002
type: single
kp: [cpp-algorithms, cpp-cpp14-17]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要把 `std::vector<float> v`（N=1M）做 `v[i] = std::sqrt(v[i]) * 2.0f + 1.0f`。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
for (float& x : v) x = std::sqrt(x) * 2.0f + 1.0f;

// B
std::transform(std::execution::unseq, v.begin(), v.end(), v.begin(),
               [](float x) { return std::sqrt(x) * 2.0f + 1.0f; });

// C
const std::size_t n = v.size();
float* p = v.data();
std::size_t i = 0;
for (; i + 8 <= n; i += 8) {
    __m256 x = _mm256_loadu_ps(p + i);
    __m256 r = _mm256_add_ps(
        _mm256_mul_ps(_mm256_sqrt_ps(x), _mm256_set1_ps(2.0f)),
        _mm256_set1_ps(1.0f));
    _mm256_storeu_ps(p + i, r);
}
for (; i < n; ++i) p[i] = std::sqrt(p[i]) * 2.0f + 1.0f;

// D
std::for_each(v.begin(), v.end(),
              [](float& x) { x = std::sqrt(x) * 2.0f + 1.0f; });
```

A. A — 朴素 range-for + std::sqrt
B. B — C++17 并行算法 + unseq 策略提示 SIMD
C. C — 手写 AVX2 intrinsic，物理上就是 SIMD
D. D — for_each + 引用 lambda

---

**解析：**

选 A。这道题考的是"现代编译器对 `std::sqrt + 基本算术` 的自动向量化已经成熟，手写 intrinsic 是反优化"。

逐一品味：

- **A**：`std::sqrt(float)` 在 GCC/Clang `-O2 -fno-math-errno`（或 `-O3`）下会被识别为可向量化的 vectorizable intrinsic，编译器直接生成 `vsqrtps` + `vfmadd` 序列。range-for 在 `vector<float>` 上展开成 `pa[i]`，已是简单数组循环——展开 + SIMD 自然发生。生成代码和 C 几乎一字不差，但**自动适应目标 ISA**：编译时若指定 `-mavx512f`，立刻变成 AVX-512 16 路。
- **B**：`execution::unseq` 是 C++17 添加的"允许在单线程内 SIMD 向量化"的策略。语义上正确，但 ① libstdc++/libc++ 的实现质量不一，有些实现仅做了 thread 并行没做 SIMD；② 即使做了 SIMD，调用路径比 A 多一层 lambda 通过 transform 内部循环间接调用，编译器需要穿透多层抽象。在主流库实现里**性能等同或略差于 A**，且代码更复杂。
- **C**：手写 AVX2 intrinsic 看似最直接，但 ① **锁死在 AVX2**——目标机器是 AVX-512 (Skylake-X 后) 时只用一半向量宽度，性能减半；目标机器只有 SSE 时直接编译失败；② `_mm256_loadu_ps` 是 unaligned load（vector 不保证 32B 对齐），如果数据本就 32B 对齐 (typical case)，aligned 版本会再快一点点；③ 写错的概率高（epilogue、对齐、混合 AVX/SSE 状态切换 penalty）。**性能 ≈ A，可移植性差、维护性差**。
- **D**：`std::for_each` + 引用 lambda 和 A 在大多数标准库实现下生成相同代码，但 ① 引用捕获让编译器有时不愿内联；② 比 A 多一层调用包装。性能等同 A 或略差，没有理由偏好。

A 最美的地方是它**让编译器为你选 ISA**：CI 在 AVX2 机器上编译就用 AVX2，在 AVX-512 机器上自动升级，未来 SVE/RVV 也自动支持。手写 C 把这种"未来收益"全部冻结。

**核心识别点：**
- 看见手写 `_mm256_*` intrinsic 在"简单数组算术"场景 → 警觉是不是在抢编译器已经会做的事
- `std::sqrt`/`std::fma` 等 cmath 函数在 `-O2 -fno-math-errno` 下编译器会识别为可向量化（早年的 errno 包袱被这个 flag 关掉）
- `execution::unseq` 在标准库实现成熟前**不一定真做 SIMD**，看产物为准
- 手写 intrinsic 的隐性代价：锁死 ISA、对齐陷阱、SSE/AVX 切换 penalty (~70 cycles)、无法跨架构
- 真正需要 intrinsic 的场景：编译器没识别出来的怪算法（permute、shuffle、scan 等）

**来源：** Matt Godbolt, "What Has My Compiler Done for Me Lately?", CppCon 2017；Intel Intrinsics Guide；Agner Fog, "The microarchitecture of Intel, AMD and VIA CPUs", §13 "AVX/SSE transition penalties".
