---
qid: cpp-perf-mem-004
type: single
kp: [cpp-classes, cpp-type-sizes]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要存 1 千万个事件记录，循环里几乎只读 `id` 和 `timestamp` 这两个字段，`payload_ptr` 偶尔才用。下面四种字段排布功能等价，哪个最值得采用？

```cpp
// A
struct Event {
    char     flag;          // 1 B
    long     timestamp;     // 8 B
    char     kind;          // 1 B
    long     id;            // 8 B
    char     priority;      // 1 B
    void*    payload_ptr;   // 8 B
};
std::vector<Event> evs(N);

// B
struct Event {
    long     id;            // 8 B   ← 热
    long     timestamp;     // 8 B   ← 热
    void*    payload_ptr;   // 8 B
    char     kind;
    char     flag;
    char     priority;
};
std::vector<Event> evs(N);

// C
struct Event {
    long     id;
    long     timestamp;
    void*    payload_ptr;
    char     kind;
    char     flag;
    char     priority;
} __attribute__((packed));
std::vector<Event> evs(N);

// D
struct Event {
    long     id;
    long     timestamp;
    void*    payload_ptr;
    char     kind;
    char     flag;
    char     priority;
};
alignas(64) struct EventPadded : Event { char pad[64 - sizeof(Event) % 64]; };
std::vector<EventPadded> evs(N);
```

A. A — 按"写代码时想到的顺序"排，可读
B. B — 把热字段放前面，冷字段塞末尾，让编译器自然 pad 到末尾
C. C — packed 取消所有 padding，结构体最小
D. D — 把每条记录补齐到 64 字节，正好对齐 cache line，整齐划一

---

**解析：**

选 B。这道题考的是"sizeof 和热字段在 cache line 里的分布共同决定循环吞吐"。

逐一品味：

- **A**：交替放 `char`/`long` 触发大量字段间 padding。`sizeof(Event)` 因对齐规则会被编译器撑到 **40 字节**（`char` 后填 7B 才能放 `long`，依次类推）。热字段 `timestamp` 和 `id` 不相邻——分别在 offset 8 和 24，跨越两段、可能跨 cache line。每条 40B，N=1e7 时数组 400 MB，循环带宽利用率低。
- **B**：把同尺寸字段聚到一起，padding 全被赶到结构体末尾。热字段 `id`/`timestamp` 在 offset 0/8 相邻，每条 cache line（64B）能放进 2 条记录的两个热字段并相邻——预取器抓一次抓两条记录的热数据。`sizeof(Event)` 也最小（24 + 3 + 5 padding = 32 字节，比 A 省 20%）。这是 *Agner Fog* §9.5 和 Drepper §3.3.1 反复推荐的"按 size 降序排"。
- **C**：`packed` 关掉对齐——`long timestamp` 现在跨边界。x86 上虽然能跑（不像 ARM 直接崩），但**每次未对齐访问可能拆成两次 load + 拼接**，热循环里直接 2–3 倍慢；编译器拿到 `packed` 还会**禁用 SIMD**，因为 vector load 要求对齐。空间省了 3 字节，速度赔上去。
- **D**：把每条记录硬塞到 64 字节。`sizeof` 从 32B → 64B，**数组总大小翻倍**，每条 cache line 只装 1 条记录而非 2 条，DRAM 带宽利用率减半。"对齐到 cache line"只在"避免 false sharing"那种特定多线程场景才有意义，对单线程顺序遍历是反优化。

**核心识别点：**
- 看见 struct 里 `char`/`long`/`char`/`long` 交替 → 警觉是不是被 padding 撑大了
- 看见 `__attribute__((packed))`/`#pragma pack` → 警觉是不是把对齐税转移到了运行时
- 看见 `alignas(64)` 强行 pad 单个记录 → 问一句"这里有 false sharing 吗"，没有就是浪费带宽
- 把字段按 size 降序排是免费的 1.2–1.5 倍加速
- `sizeof(struct)` 是衡量数组带宽的最关键数字

**来源：** Agner Fog, "Optimizing software in C++", §9.5 "Cache contentions in large data structures"；Ulrich Drepper, "What Every Programmer Should Know About Memory", §3.3.1；Intel Optimization Reference Manual, §3.6.4 "Alignment".

## Explanation

选项关键是结构体字段重排：按对齐需求从大到小排列可减少 padding，让数组更紧凑并提高 cache line 利用率。packed 虽然省空间，但可能制造未对齐访问，反而把成本转到运行时。误区是盲目 alignas(64)；没有 false sharing 时，它只会浪费带宽。
