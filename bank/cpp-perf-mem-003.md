---
qid: cpp-perf-mem-003
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要在 100 万个 `int` 上做累加。下面四个写法功能完全一样，哪个最值得采用？

```cpp
// A
std::list<int> xs;
for (int i = 0; i < 1'000'000; ++i) xs.push_back(i);
long long s = 0;
for (int x : xs) s += x;

// B
std::deque<int> xs;
for (int i = 0; i < 1'000'000; ++i) xs.push_back(i);
long long s = 0;
for (int x : xs) s += x;

// C
std::vector<int> xs;
xs.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i) xs.push_back(i);
long long s = std::accumulate(xs.begin(), xs.end(), 0LL);

// D
std::forward_list<int> xs;
for (int i = 999'999; i >= 0; --i) xs.push_front(i);
long long s = 0;
for (int x : xs) s += x;
```

A. A — list 双向链，方便后续中间插入，先建好结构再说
B. B — deque 分段连续，比 vector 更不怕大尺寸扩容
C. C — vector 一次 reserve 再 push_back，遍历用 accumulate
D. D — forward_list 单链，开销更小，等价于精简版 A

---

**解析：**

选 C。这道题考的是"被遍历的容器选错，等于把 L1 命中率从 95% 改成 5%"。

逐一品味：

- **A**：`std::list` 每个节点至少 `sizeof(int) + 2*sizeof(void*) = 20` 字节（实际带分配器对齐 ~32 字节），节点地址来自堆分配器，相邻节点几乎不连续。遍历时每读一个 int 都伴随一次指针追逐：硬件预取器无法预测下一个地址，每次访问都可能 cache miss。100 万次随机访问，主流硬件 ~200 cycles/DRAM，整体比 C 慢 **15–50 倍**。Stroustrup 在 GoingNative 2012 用同样实验证过：vector 在"遍历"场景压倒所有链式容器。
- **B**：`std::deque` 是分段数组（典型 4KB 一段），段内连续、段间跳。遍历时大部分迭代是顺序的，但每跨段一次预取链断一次，且迭代器递增比 vector 多一次"是否到段尾"的判断。比 C 慢 **2–4 倍**。
- **C**：`reserve` 一次解决所有重分配，`push_back` 退化成"写内存 + 移 size"。底层是一整段连续内存（100 万 int = 4 MB），刚好流式吃满 L2/L3 → DRAM 带宽。`std::accumulate` 编译器能自动向量化成 SIMD 加法。是基线，**最快**。
- **D**：`forward_list` 比 `list` 节点小一个指针，但其它特征完全一样：随机地址、指针追逐、零空间局部性。比 A 略快一点（节点小一点能多塞进一个 cache line），但仍比 C 慢 **10–30 倍**。

**核心识别点：**
- 看见"我要的就是个序列、之后只是遍历/累加" → 绝大多数情况答案是 `vector`，不要因为"将来可能插入"就提前用链表
- 看见 `list`/`forward_list` 出现在"线性扫描密集"的代码里 → 几乎都是错的选择
- 一个 `list<int>` 节点 32B 但有效数据 4B，**带宽利用率 12.5%**；vector<int> 是 100%
- `reserve` 之后 `push_back` 等价于裸指针写，是建容器的标准姿势

**来源：** Stroustrup, "Why you should avoid Linked Lists", GoingNative 2012；Chandler Carruth, "Efficiency with Algorithms, Performance with Data Structures", CppCon 2014；Bjarne Stroustrup, "The C++ Programming Language" 4th ed., §31.4.
