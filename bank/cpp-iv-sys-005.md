---
qid: cpp-iv-sys-005
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google, 华为]
rubric:
  - 解释 CPU 缓存层次（L1/L2/L3）及缓存行（cache line，通常 64 字节）概念
  - 空间局部性：连续访问内存比随机访问快（行优先 vs 列优先矩阵遍历）
  - 时间局部性：近期访问的数据复用
  - 数据结构优化：SoA vs AoS，字段对齐与 padding，热/冷数据分离
  - 加分：False Sharing 问题及 alignas(64) 修复方案
---

# 缓存友好代码是什么？如何优化数据结构以提高缓存命中率？

## Explanation

### CPU 缓存基础

现代 CPU 访问内存的延迟差异极大：

| 层次 | 延迟（周期） | 容量典型值 |
|------|------------|-----------|
| 寄存器 | 0–1 | 几十个 |
| L1 缓存 | ~4 | 32–64 KB |
| L2 缓存 | ~12 | 256 KB–1 MB |
| L3 缓存 | ~40 | 8–32 MB |
| 主内存（DRAM） | ~200 | 数 GB |

CPU 以**缓存行（cache line，64 字节）**为最小单位从内存加载数据。一次 cache miss 导致整行从内存加载。

### 空间局部性（Spatial Locality）

访问连续内存比随机跳跃快得多，因为加载一个元素会连带拉入相邻 63 字节。

**反例：列优先访问 C 行优先二维数组**

```cpp
// 每次内存跳跃 N*sizeof(int) 字节，大量 cache miss
for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++)
        sum += a[i][j];  // 跨行访问

// 正确：行优先遍历，顺序访问
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        sum += a[i][j];  // 连续地址，极好的空间局部性
```

### 时间局部性（Temporal Locality）

近期访问的数据很快会被再次访问，应保留在缓存中。循环中重复读取同一小数组比每次读取不同大数组高效。

### AoS vs SoA（数组的结构 vs 结构的数组）

```cpp
// AoS（Array of Structs）— 混合热/冷字段
struct Particle { float x, y, z, vx, vy, vz; int id; char name[32]; };
Particle particles[N];
// 若只需遍历 x/y/z，每个 Particle 加载 52 字节却只用 12 字节

// SoA（Struct of Arrays）— 分离热字段
struct Particles {
    float x[N], y[N], z[N];      // 热数据：物理模拟每帧都访问
    float vx[N], vy[N], vz[N];
    int   id[N];
    char  name[N][32];            // 冷数据：渲染/调试时才用
};
// 遍历 x/y/z 时，64 字节 cache line 装 16 个 float，命中率极高
```

### 字段对齐与 False Sharing

**避免无意义 padding**（有时需重排字段顺序以减小结构体大小）：

```cpp
// 浪费：bool(1) + padding(3) + int(4) + double(8) = 16 字节
struct Bad  { bool flag; int count; double value; };
// 紧凑：double(8) + int(4) + bool(1) + padding(3) = 16 字节（同）→ 按大到小排列
struct Good { double value; int count; bool flag; };
```

**False Sharing（伪共享）**：多线程各自操作不同变量，但它们恰好落在同一缓存行上，导致 L1 缓存频繁失效：

```cpp
// 错误：counter[0] 和 counter[1] 可能在同一 cache line
int counter[2];

// 修正：每个计数器独占一个 cache line
struct alignas(64) PaddedCounter { int value; };
PaddedCounter counter[2];
```

### 实战经验

- 热路径中优先使用 `std::vector`（连续）而非 `std::list`（指针链）。
- 小对象 arena 分配比 `new` 散射分配缓存友好。
- 使用 `perf stat -e cache-misses,cache-references` 量化优化效果，而非凭感觉。
