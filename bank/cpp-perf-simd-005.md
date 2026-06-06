---
qid: cpp-perf-simd-005
type: single
kp: [cpp-algorithms, cpp-iterators]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: D
tags: [performance, code-taste]
---

要从 `std::vector<int> v`（N=1M）取出所有偶数，每个乘 3，求和。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
std::vector<int> evens;
std::copy_if(v.begin(), v.end(), std::back_inserter(evens),
             [](int x){ return x % 2 == 0; });
std::vector<int> tripled(evens.size());
std::transform(evens.begin(), evens.end(), tripled.begin(),
               [](int x){ return x * 3; });
long s = std::accumulate(tripled.begin(), tripled.end(), 0LL);

// B
auto r = v | std::views::filter([](int x){ return x % 2 == 0; })
           | std::views::transform([](int x){ return x * 3; });
long s = 0;
for (int x : r) s += x;

// C
long s = std::accumulate(v.begin(), v.end(), 0LL,
    [](long acc, int x) { return (x % 2 == 0) ? acc + x * 3 : acc; });

// D
long s = 0;
for (int x : v)
    if ((x & 1) == 0) s += x * 3;
```

A. A — 三步分明：过滤、变换、求和
B. B — C++20 ranges 视图链式表达
C. C — accumulate 内联 if 判断
D. D — 一个 for 循环融合过滤、变换、累加

---

**解析：**

选 D。这道题考的是"loop fusion：能在一个循环里做完的事，被拆成三遍是 3 倍的内存流量"。

逐一品味：

- **A**：① `copy_if` 第一遍：扫描 N 个 int，分配 evens（最坏 N int = 4 MB），写一半；② `transform` 第二遍：再扫描 N/2 int，分配 tripled，写 N/2 int；③ `accumulate` 第三遍：再扫描 N/2 int。**总内存读 = 2N int，写 = N int，加 2 次堆分配**。L3 cache (~MB 量级) 一次都装不下。比 D **慢 3–6 倍**，还多用 8 MB 临时内存。
- **B**：ranges views 是 lazy 的——`filter | transform` 不分配中间容器，只在最终循环里逐元素 pull-evaluate。理论上和 D 等价。**实际上**：① C++20 ranges 在 GCC ≤13 / Clang ≤16 的实现对 filter view 优化不彻底，迭代器 `operator++` 内部要跳到下一个匹配元素，引入条件分支让编译器有时无法向量化；② lambda + 迭代器嵌套层次深，inline 后代码膨胀。**性能常常比 D 慢 1.5–3 倍**，取决于编译器版本。语义优雅但生成代码不稳。
- **C**：`accumulate` + ternary 在一个循环里完成，但 `accumulate` 是严格左折叠（见 simd-003 题）——单累加器、长依赖链，**无法 SIMD**。比 D 慢 2–4 倍。语义上对了，性能 API 选错了。
- **D**：**单循环，零临时内存**：v 流式扫一遍 (~4 MB)，每个元素做一次 `x & 1` 测试 + 条件加。`x & 1` 是 1 cycle、`x * 3` 是 1 cycle（编译器用 `lea` 或 `imul`）。配合自动展开 + SIMD（GCC `-O3` 能识别为带条件累加的 reduction，AVX2 用 `vpand` + `vpaddd`），吞吐达内存带宽极限。**最快**，代码也最短。

D 是 *loop fusion* 原则的教科书例子：每多扫一遍数据就多付一遍内存带宽，当工作集超过 L3 时这个代价是数量级的。

**核心识别点：**
- 看见数据流水"copy_if → transform → accumulate"分三步 → 警觉每一步都把数据再扫一遍 + 临时分配
- 看见 C++20 ranges views → 注意当前编译器版本的实现质量，看 godbolt
- 看见 `accumulate + 条件` → 警觉单累加器禁用 SIMD
- *Loop fusion*：把"几个简单循环"融成一个，能省下 (循环数-1)·N 字节的内存流量
- 当处理数据 > L3 size 时，**少扫一遍 = 数量级的差异**

**来源：** Eric Niebler, "Ranges for the Standard Library", CppCon 2015；Sean Parent, "C++ Seasoning", GoingNative 2013（"no raw loops"vs"循环融合"的张力）；Drepper, "What Every Programmer Should Know About Memory", §3.3 "Cache implementations".
