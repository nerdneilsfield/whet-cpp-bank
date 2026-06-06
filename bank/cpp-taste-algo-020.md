---
qid: cpp-taste-algo-020
type: single
kp: [cpp-algorithms, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---

对一个大数组（1000 万个 int）求所有元素的和。下面四种策略，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v(10'000'000);
// ... fill v ...
auto sum = std::accumulate(v.begin(), v.end(), 0LL);

// B
std::vector<int> v(10'000'000);
// ... fill v ...
auto sum = std::reduce(std::execution::par_unseq,
                       v.begin(), v.end(), 0LL);

// C
std::vector<int> v(10'000'000);
// ... fill v ...
long long sum = 0;
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < (int)v.size(); ++i) {
    sum += v[i];
}

// D
std::vector<int> v(10'000'000);
// ... fill v ...
auto sum = std::reduce(std::execution::seq,
                       v.begin(), v.end(), 0LL);
```

A. A — accumulate，标准串行求和

B. B — 用 par_unseq 并行 reduce，发挥多核

C. C — OpenMP 并行规约，手写

D. D — seq reduce 和 accumulate 相同，但多了 abstraction

---

**解析：**

选 B。对于 1000 万 int 的求和，数据量足够大，并行加速明显（通常 4-6x），且 `reduce` + `par_unseq` 是 C++17 标准提供的并行算法入口，不依赖外部工具链。

逐一品味为什么其他版本不好：

- **A**：`accumulate` 串行求和。1000 万个 int 串行在现代 CPU 上大约 20-40ms。但如果有多核可用（现代桌面至少有 8 个性能核），完全可以让 CPU 满负载工作。`accumulate` 没有利用可交换加法的并行潜力。

- **C**：OpenMP 是 C/C++ 扩展而非标准 C++，需要编译器特定支持（`-fopenmp`）。代码不再可移植到 MSVC 或所有嵌入式环境。而且手写 `#pragma omp parallel for reduction` 是在重新发明 `std::reduce` 做的事。

- **D**：`reduce(execution::seq, ...)` 在语义上等价于 `accumulate`，多了抽象层但没有收益。`seq` 策略就是"强制串行"，和 `accumulate` 的区别只在于 reduce 不保证顺序（int 加法可交换，不影响结果）。用 `seq` 不如直接用 `accumulate`。

B 的 `par_unseq` 告诉标准库："这个操作可以并行 + 向量化"。实现会拆分任务到多个线程，每个线程对一段连续区域求和，最后合并。这是标准委员会给出的"并行求和"入口。

但注意：**不是所有场景都应该用 `par`**：
- 数据量小时（< 1 万），并行调度开销 > 加速收益
- 操作不是可交换/可结合的，不能 `reduce`（必须用 `accumulate`）
- 容器不支持随机访问迭代器（某些并行 algorithm 有迭代器要求）

核心识别点：
- 大数组 + 可交换操作 → `reduce` + `par_unseq` / `par`
- 小数组 / 非可交换 → `accumulate`
- OpenMP / TBB / 手写线程池都是次选——标准库已经有入口
- `par_unseq` 允许向量化（SIMD），是比 `par` 更强的承诺
- 不要对所有求和都上并行——评估数据量和计算密度后再决定