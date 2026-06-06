---
qid: cpp-perf-mem-001
type: single
kp: [cpp-stl-basics, cpp-arrays-pointers]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: D
tags: [performance, code-taste]
---

要遍历 1 千万个粒子，只读 `x` 字段做累加。下面四个布局功能等价，哪个最值得采用？

```cpp
// A
struct Particle { double x, y, z, vx, vy, vz, mass, charge; };
std::vector<Particle> ps(N);
double s = 0;
for (auto& p : ps) s += p.x;

// B
struct Particle { double x, y, z, vx, vy, vz, mass, charge; };
std::vector<std::unique_ptr<Particle>> ps(N);
for (auto& p : ps) p = std::make_unique<Particle>();
double s = 0;
for (auto& p : ps) s += p->x;

// C
struct Particle { double x, y, z, vx, vy, vz, mass, charge; };
std::list<Particle> ps(N);
double s = 0;
for (auto& p : ps) s += p.x;

// D
struct Particles {
    std::vector<double> x, y, z, vx, vy, vz, mass, charge;
};
Particles ps;
ps.x.resize(N); ps.y.resize(N); /* ... */
double s = 0;
for (auto v : ps.x) s += v;
```

A. A — 把粒子放在连续 vector 里，最自然的对象建模
B. B — 多一层间接，但每个 Particle 独立分配，方便单独释放
C. C — list 节点连续插入快，做累加遍历也一样
D. D — 把字段拆开存，写起来不像 OOP 但循环里只摸到要用的那一列

---

**解析：**

选 D。这道题考的是"只读一个字段时，硬件实际从内存搬了多少字节"。

逐一品味：

- **A**：`Particle` 共 64 字节，正好一条 cache line。循环里只用 `x`（8 字节），但 CPU 每次都把整条 64 字节搬上来——**有效带宽利用率 8/64 = 12.5%**。1 千万个粒子 = 640 MB 流入 L2/L3，远超 L3 容量，最终走 DRAM，~200 cycles/line。
- **B**：在 A 的基础上再加一层指针跳转。`unique_ptr` 通过 `new` 分配每个粒子，地址随机，预取器几乎无法工作，每次 `p->x` 是一次随机访问，TLB miss + cache miss 叠加，比 A 还慢 **3–10 倍**。
- **C**：`std::list` 每个节点除了 `Particle` 还有前后指针 + 分配器 headroom，节点之间地址不连续，遍历时硬件预取器完全瞎掉。实测 list 累加比 vector 慢 **10–50 倍**，Bjarne Stroustrup 在 GoingNative 2012 用同样实验证过 list 在几乎所有"遍历型"场景都输。
- **D**：把字段按列存，循环只读 `x` 那一列。每条 cache line 装 8 个 `double`，**带宽利用率 100%**。N=1e7 时 `x` 总共 80 MB，预取器顺序流式抓取，吞吐接近 DRAM 峰值；自动向量化也能直接吃满 256/512-bit 寄存器。相比 A **快 4–8 倍**，相比 B/C 一两个数量级。

**核心识别点：**
- 看见"循环里只用结构体一两个字段、其它字段躺着不动" → 警觉 AoS 是不是浪费带宽，应转 SoA
- 看见 `vector<unique_ptr<T>>` 做密集遍历 → 警觉一层间接 + 随机地址，整数倍变慢
- 看见 `std::list` 做累加/扫描 → 几乎总是错的选择
- 一条 cache line 64 字节是基本计量单位，凡是"搬了用不上的字节"都是隐性带宽税

**来源：** Mike Acton, "Data-Oriented Design", CppCon 2014；Stroustrup, "Why you should avoid Linked Lists", GoingNative 2012；Agner Fog, "Optimizing software in C++", §9.

## Explanation

正确选择通常是顺序访问连续内存，因为它最符合 cache line 和硬件预取器的工作方式。链表、指针跳转或随机访问会把每个元素变成潜在 cache miss。常见误区是只比较容器操作复杂度，忽略 vector 的空间局部性常常压倒理论上的插入删除优势。
