---
qid: cpp-perf-branch-005
type: single
kp: [cpp-functions, cpp-arrays-pointers]
primary_kp: cpp-functions
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要把 `data[i] *= k` 跑 N 次，其中 `k` 由 `compute_factor(data)` 算出（不随 i 变化）。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
void scale(double* data, std::size_t n, double* k_ptr) {
    *k_ptr = compute_factor(data);
    for (std::size_t i = 0; i < n; ++i)
        data[i] *= *k_ptr;
}

// B
void scale(double* data, std::size_t n) {
    const double k = compute_factor(data);
    for (std::size_t i = 0; i < n; ++i)
        data[i] *= k;
}

// C
void scale(double* __restrict__ data, std::size_t n, double* __restrict__ k_ptr) {
    *k_ptr = compute_factor(data);
    for (std::size_t i = 0; i < n; ++i)
        data[i] *= *k_ptr;
}

// D
void scale(double* data, std::size_t n, double* k_ptr) {
    *k_ptr = compute_factor(data);
    double tmp_k = *k_ptr;
    for (std::size_t i = 0; i < n; ++i)
        data[i] *= tmp_k;
}
```

A. A — 让函数把 k 留给调用者用，循环里每次重读最新值
B. B — 把 k 算进局部 const，再在循环里用
C. C — 加 __restrict__ 告诉编译器 data 和 k_ptr 不重叠
D. D — 在循环外手工把 *k_ptr load 到栈变量，效果和 B 一样

---

**解析：**

选 B。这道题考的是"编译器何时能/不能把循环不变量提到循环外（LICM）"。

逐一品味：

- **A**：`*k_ptr` 在循环里看似不变，但编译器**必须假设 `data[i]` 的写入可能修改 `*k_ptr`**——因为 `data` 和 `k_ptr` 都是 `double*`，C++ 别名规则下两者可能指向重叠内存（strict aliasing 允许同类型指针互相别名）。所以编译器不敢做 LICM，每次循环都重新 load `*k_ptr` —— **每次 store data[i] 后还要 load k**。多了 N 次内存 load，破坏了乘法的 throughput；更糟的是阻止了向量化。比 B 慢 **2–4 倍**。
- **B**：`k` 是局部变量，没人能从外部修改它，编译器立刻知道它在循环里不变，自动 LICM；并能放进 SIMD 寄存器广播给 4/8 路并行乘法。零额外内存访问，循环退化成纯计算 + 顺序 store。**最佳实践**——把循环不变量显式拷贝到局部 const，是最简单的"喂给编译器明确的语义"。
- **C**：`__restrict__` 是 GCC/Clang 扩展（C99 标准但 C++ 没有），告诉编译器两个指针不重叠。理论上能让编译器做和 B 一样的优化。但 ① 非标准、跨编译器行为不一；② 接口仍然丑——为什么非要把 k 通过指针传出？这是在用复杂手段修一个本不该存在的复杂性。性能可能等同 B，但代码差。
- **D**：和 A 在编译器眼里几乎一样——`tmp_k = *k_ptr` 只发生一次，但循环里仍用 `tmp_k`。等等，这是 B 的等价写法！再看一眼……`tmp_k` 是局部变量，循环里读它编译器知道不变。**性能等价 B**。但啰嗦——B 用 const 一行解决，D 需要两行且更易写错（写成循环里再重读 `*k_ptr` 就退化成 A）。功能上和 B 同，代码差。

B 优于 D 的关键不是性能（一样），而是**意图明确性**：B 一开始就把 k 标 const，让"循环不变"成为编译器/读者都看得见的事实。

**核心识别点：**
- 看见循环里访问"通过指针传进来的不变量"→ 警觉编译器是不是被别名规则卡住做不了 LICM
- 看见 `__restrict__`/`__restrict` → 警觉是不是在补救一个本不该有的别名问题
- 把循环不变量在循环外赋值给 `const` 局部变量是**最便宜的"喂给编译器语义"的技巧**
- 编译器对"指针参数 vs 局部变量"的别名假设强度天差地别
- 一个看不到的 alias 假设能杀掉向量化的整数倍收益

**来源：** Chandler Carruth, "Tuning C++: Benchmarks, and CPUs, and Compilers!", CppCon 2015；Agner Fog, "Optimizing software in C++", §8 "Loop optimizations"；GCC manual, `__restrict__`.

## Explanation

正确选择应减少循环内难预测分支，并让循环体保持简单。排序、分桶或先过滤再处理有时能把随机分支变成连续批处理，换取更好的预测和缓存行为。常见误区是只看算法大 O，而忽略同为 O(n) 时分支模式会造成数量级常数差异。
