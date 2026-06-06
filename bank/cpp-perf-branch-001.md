---
qid: cpp-perf-branch-001
type: single
kp: [cpp-algorithms, cpp-control-flow]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要统计 `std::vector<int> data`（1 千万个 0–255 均匀随机数）中 `>= 128` 的元素之和。下面四个写法功能完全相同，哪个最值得采用？

```cpp
// A
long s = 0;
for (int x : data)
    if (x >= 128) s += x;

// B
std::sort(data.begin(), data.end());
long s = 0;
for (int x : data)
    if (x >= 128) s += x;

// C
long s = 0;
for (int x : data) {
    int mask = -(x >= 128);
    s += x & mask;
}

// D
long s = 0;
for (int x : data)
    s += (x >= 128) ? x : 0;
```

A. A — 朴素 if 累加
B. B — 先排序再 if 累加，相同的循环体
C. C — 用位掩码消去 if，全分支自由
D. D — 用三元表达式替代 if

---

**解析：**

选 B。这道题是 Stack Overflow 上 *"Why is processing a sorted array faster?"* 的活字典版本。

逐一品味：

- **A**：在随机数据上 `x >= 128` 大约 50% 真 50% 假，分支预测器（Intel 用 TAGE、AMD 用感知机）无法学到任何模式，误判率接近 50%。每次误判流水线刷新 ~15–20 cycles，加上整个循环就 50% 误判率 × 20 cycles ≈ 10 cycles/iteration。
- **B**：排序后数组前半全是 `<128`、后半全是 `>=128`，分支转变只发生 1 次。预测器**几乎 100% 命中**，分支几乎免费，循环退化成一次比较 + 一次条件加（~1–2 cycles/iteration）。即使把排序的 O(N log N) ~600ms 算进去，**循环本身比 A 快 6–10 倍**——这就是著名的 SO 答案的数据。仅当循环要跑多次或排序代价能摊销时才整体划算（题目场景就是如此）。
- **C**：消除了 if，但引入了**数据依赖**——`mask` 和 `s` 都依赖前一次的 x，且 `&` 操作链化。编译器在 A 上往往能用 `cmov` 自动消去分支，C 这种手写 mask 不一定比编译器更聪明，且阻碍了某些向量化路径。性能和 A 接近，不一定更快。
- **D**：三元表达式在 C++ 里和 if 语义等价，**编译器生成的代码几乎一样**（往往都用 `cmov`）。性能与 A 相同，没有任何优势。

B 的妙处在于它没改算法、没改循环体，只是**预处理数据**让硬件预测器工作得好——这是"理解硬件"的典型胜出。

**核心识别点：**
- 看见"在随机数据上做条件累加，循环体里有 if" → 警觉是不是 50% 误判率，是不是值得排序
- 看见手写位运算消去 if → 警觉编译器在 cmov 时代是不是已经做了同样的事
- 数据的统计性质（已排序/已分组）能让分支预测命中率从 50% 跳到 99%
- 一次分支误判代价 ~15–20 cycles，循环很大时这是数倍的差异

**来源：** Stack Overflow 经典问答 "Why is processing a sorted array faster than processing an unsorted array?"；Agner Fog, "The microarchitecture of Intel, AMD and VIA CPUs", §3 "Branch prediction"；Intel Optimization Reference Manual, §3.4 "Branch Prediction".

## Explanation

选项核心在于分支预测：如果条件分布稳定且可预测，普通 if 往往已经很快；如果数据随机，分支错误会让流水线反复清空。正确答案选择能减少不可预测分支或让编译器生成条件移动/向量化的写法。常见误区是只数语句数量，忽略一次 mispredict 的代价远高于几条整数指令。
