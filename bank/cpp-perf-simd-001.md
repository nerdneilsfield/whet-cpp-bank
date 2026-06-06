---
qid: cpp-perf-simd-001
type: single
kp: [cpp-algorithms, cpp-arrays-pointers]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要把两个 `std::vector<float>` 逐元素相加到第三个。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
void add(const std::vector<float>& a, const std::vector<float>& b,
         std::vector<float>& c) {
    const std::size_t n = a.size();
    const float* pa = a.data();
    const float* pb = b.data();
    float* pc = c.data();
    for (std::size_t i = 0; i < n; ++i)
        pc[i] = pa[i] + pb[i];
}

// B
void add(const std::vector<float>& a, const std::vector<float>& b,
         std::vector<float>& c) {
    for (std::size_t i = 0; i < a.size(); ++i)
        c.at(i) = a.at(i) + b.at(i);
}

// C
void add(const std::vector<float>& a, const std::vector<float>& b,
         std::vector<float>& c) {
    std::transform(a.begin(), a.end(), b.begin(), c.begin(),
                   [](float x, float y) { return x + y; });
}

// D
void add(const std::vector<float>& a, const std::vector<float>& b,
         std::vector<float>& c) {
    auto ia = a.begin(); auto ib = b.begin(); auto ic = c.begin();
    while (ia != a.end()) { *ic++ = *ia++ + *ib++; }
}
```

A. A — 提取 raw pointer 后用 size_t 索引
B. B — 用 .at 做下标，安全且代码意图清晰
C. C — 标准 transform + lambda，最现代
D. D — 三个迭代器并行推进，纯 STL 风格

---

**解析：**

选 A。这道题考的是"编译器自动向量化的几个硬性前提，哪种写法满足全部"。

逐一品味：

- **A**：① **行程数 n 在循环开始前 const 化** → 编译器知道范围，可生成 epilogue；② **指针拷贝到局部变量** → 编译器知道循环里没人改 a/b/c 的大小；③ 简单 `c[i] = a[i] + b[i]` 没有任何依赖链。对 `float` 数组，AVX2 一条 `vaddps` 处理 8 个 float，编译器直接生成展开 + SIMD 的循环。**最快**，达到内存带宽极限。
- **B**：`.at()` 每次调用**做一次范围检查 + 可能抛 `out_of_range`**。`at` 的异常路径让编译器无法去掉边界检查（除非 LTO + 全 inline + 充分推断），通常每次循环多 1 个 cmp + 1 个分支。**禁用向量化**（编译器不敢把"可能抛异常"的调用合并到 SIMD 里）。比 A 慢 **5–10 倍**。
- **C**：`std::transform` + lambda 在 libstdc++/libc++ 里通常是简单的"调用 op 在每个元素上"，应当能被内联和向量化。但 `lambda` 内联到 `transform` 内部循环需要编译器穿透两层抽象——`-O2` 不一定能；`-O3` 一般可以但**生成代码常常和 A 等价或略差**（取决于编译器版本）。问题是 `transform` 内部循环用迭代器，对 `vector::iterator` 编译器需要先看穿迭代器 = 指针，再 hoist 出 end 比较。有时编译器吃满优化能等于 A，有时差几倍。**不稳定**。
- **D**：用迭代器 + `while`，循环条件 `ia != a.end()` 每次重新 load `a.end()`（编译器需要看穿迭代器、保证 a 没被修改才能 hoist）。三个独立的指针递增是依赖链。比 A 慢，理论上编译器能优化但实际常常 1.5–3× 差距。

A 的好处是**用人类对编译器的同情心**：先把所有"循环里不变的东西"显式提到循环外（n、原始指针），让编译器以最少的推理量识别"简单数组遍历"模式，立刻向量化。这是 numpy/eigen 等高性能库内部循环长成的样子。

**核心识别点：**
- 看见循环内反复调用 `.size()`/`.end()` → 警觉编译器能不能 hoist，不行的话每次循环多一次 load
- 看见 `.at()` 出现在数值密集循环 → 警觉异常路径阻断 SIMD
- 看见 `std::transform` 等高阶算法 → 在简单 op 上**应当**能展开到 SIMD，但需检查 godbolt 实际产物
- 自动向量化的硬性前提：行程数已知（或可推算）、没有依赖链、内存不重叠（或编译器能证明）、没有异常路径、循环体简单
- 一条 AVX2 `vaddps` = 1 cycle 处理 8 个 float，SIMD-on 和 SIMD-off 的差距是 4–8×

**来源：** Agner Fog, "Optimizing software in C++", §12 "Using vector operations"；Intel Optimization Reference Manual, §3.8 "Auto-vectorization"；Matt Godbolt, "What Has My Compiler Done for Me Lately?", CppCon 2017.

## Explanation

选 A，因为原始指针加固定循环边界最容易被编译器识别为无异常、连续、简单的数组循环。`.at()` 的边界检查和异常路径会妨碍向量化；迭代器和 `transform` 理论上可优化，但更依赖编译器穿透抽象。误区是认为更“STL 风格”一定生成同样代码，性能热循环仍应关注实际向量化条件。
