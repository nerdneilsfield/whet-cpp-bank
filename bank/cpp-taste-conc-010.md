---
qid: cpp-taste-conc-010
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
要实现一个"线程安全的请求计数器"——多线程对其 +1，最后读总数。四个版本功能相同，哪个品味最好？

```cpp
// A
std::atomic<long> n_a{0};
void inc_a() { n_a.fetch_add(1, std::memory_order_relaxed); }
long read_a() { return n_a.load(); }  // 默认 seq_cst

// B
std::atomic<long> n_b{0};
void inc_b() { n_b += 1; }
long read_b() { return n_b.load(); }

// C
std::atomic<long> n_c{0};
void inc_c() { n_c.fetch_add(1, std::memory_order_seq_cst); }
long read_c() { return n_c.load(std::memory_order_seq_cst); }

// D
std::atomic<long> n_d{0};
void inc_d() { ++n_d; }
long read_d() { return n_d; }
```

A. A — `fetch_add(1, memory_order_relaxed)` 显式声明只要原子性、不要全序保证，性能最优
B. B — `+= 1` 简洁，编译器自动用默认内存序
C. C — `seq_cst` 是最强的内存序，最安全
D. D — `++n_d` 和 `return n_d`，最简洁不啰嗦

---

**解析：**

选 A。这道题考 **"独立计数器 vs 内存序的精确选择"**——这是 atomic 题最经典的品味分水岭。

`fetch_add` 默认就是 `seq_cst`（顺序一致），编译器要在每个 atomic 操作前后插入完整内存屏障，在 x86 上是 `MFENCE`/`LOCK` 指令、在 ARM 上是 `DMB ISH`。**但纯计数器场景里，"哪次 +1 在哪次 +1 之前发生"并不重要**——我们只要最后总数准就行。这正是 `memory_order_relaxed` 的精确语义：**保证原子性，不保证和其他变量的顺序关系**。在高频计数场景下，relaxed 在 ARM 上能给到 3-5 倍吞吐。

`read_a()` 用默认 `seq_cst` 是有意为之——读的那一刻我们要拿到一个"看起来全局一致"的快照，且读频率远低于写，开销可接受。**写和读用不同 memory_order 是正确的细分**。

逐一品味：

- **B / D**：`+= 1` 和 `++n_d` 是 `atomic` 重载的运算符，**默认 `memory_order_seq_cst`**。语法糖看起来友好，但**隐藏了内存序选择**——读者看不出作者是不是有意要 seq_cst、还是只是图省事。在性能敏感的计数场景里这是"默认即过强"。B 和 D 在功能上完全等价（运算符重载就是这样），区别只是 D 的 `return n_d` 隐式转换、B 的 `n_b.load()` 显式调用——但**都没解决核心问题：内存序没显式表达**。
- **C**：所有操作都明写 `seq_cst`——意图清晰，但"清晰地表达了一个错的决定"。计数器不需要 seq_cst。**显式选了错的，比隐式选了错的更刺眼**——它告诉读者"作者想过这个问题，但选错了"。

**核心识别点：**

- 纯计数器（不和其他变量配合）→ `fetch_add(1, memory_order_relaxed)`
- 看见 `atomic<int> x; ++x;` → 警觉隐式 seq_cst，问问是不是真要这么强
- 看见所有原子操作都 `seq_cst` → 警觉是不是"宁严勿宽"的懒惰
- 用 atomic 做"flag + 数据"组合（如 lock-free 单例的指针） → 必须 acquire/release
- 真需要全序保证（多个原子变量之间有约束） → seq_cst 才不算过度

memory_order 选择有个简单口诀：
- 单变量计数 → relaxed
- 一处写、多处读的"配对"语义（如指针发布）→ release / acquire
- 多变量需要全局总序（如 Dekker 算法）→ seq_cst

A 选了 relaxed 不是"为了快"——是**精确表达"我只需要计数、不需要顺序"这个语义**。relaxed 不是"不安全的弱选项"，是**和需求严格匹配的精确选项**。把"宁选最强"当品味是误读——选过强等于声明了一个不存在的不变式，对读者是噪音，对编译器是优化阻碍。

**来源：** 手写题。Memory order 选择见 Herb Sutter "atomic Weapons" (C++ and Beyond 2012, 共 3 小时 talk)；relaxed 计数器示例见 ISO/IEC 14882:2017 §32.4 [atomics.order] 的 example 1；Anthony Williams *C++ Concurrency in Action* 2e §5.3.3 详细对比了各内存序的开销。

## Explanation

正确答案是 A。写和读用不同 memory_order 是正确的细分。
逐一品味： B / D：`+= 1` 和 `++n_d` 是 `atomic` 重载的运算符，默认 `memory_order_seq_cst`。
语法糖看起来友好，但隐藏了内存序选择——读者看不出作者是不是有意要 seq_cst、还是只是图省事。
