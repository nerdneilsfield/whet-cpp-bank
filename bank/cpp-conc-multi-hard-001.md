---
qid: cpp-conc-multi-hard-001
type: multi
kp: [cpp-concurrency]
difficulty: hard
answer_key: [A, B, D]
---
关于 `std::memory_order` 的语义，以下说法正确的是哪些？

```cpp
std::atomic<int> x{0}, y{0};
int r1, r2;

// Thread 1
x.store(1, std::memory_order_release);

// Thread 2
r1 = x.load(std::memory_order_acquire);
y.store(1, std::memory_order_relaxed);
```

A. `memory_order_relaxed` 仅保证该原子操作本身的原子性，对其他变量没有任何同步或顺序保证；可重排到任意位置。
B. `acquire`/`release` 形成的"释放-获取"配对，保证 release 之前的写入对 acquire 之后的读取可见，但只在该原子变量上同步。
C. `seq_cst` 是单个线程内的顺序约束，对跨线程没有任何额外保证，性能与 `acquire/release` 完全一致。
D. `memory_order_consume` 在标准中存在但实际编译器普遍按 `acquire` 实现，C++17 起在规范中被建议避免使用。

---

**解析：**

A 正确：relaxed 仅承诺原子性与该原子变量的单一全序，对其他普通/原子变量的可见性、顺序不做任何承诺，是最弱的内存序。
B 正确：release-acquire 同步建立了 happens-before 关系——release 之前所有副作用（包括非原子写）对其后 acquire 之后的读可见；这个同步关系是通过同一个原子变量建立的。
C 错误：`seq_cst` 是**最强**的顺序，所有 seq_cst 操作在所有线程上形成单一全局序（Sequential Consistency），代价最高（典型实现需 `mfence` 或 `lock`），不只是单线程顺序。
D 正确：`consume` 旨在比 acquire 更便宜（只保证数据依赖链上的同步），但实现复杂且优化器易破坏依赖链，几乎所有编译器把它退化为 `acquire`，标准中已暂时弃用并劝退使用。

## Explanation

A、B、D 正确：`relaxed` 只保证单个原子操作的原子性，不建立对其他数据的同步。release/acquire 必须通过同一原子变量配对，才能把释放前写入对获取后读取可见。常见误区是认为 `seq_cst` 只影响单线程顺序；它还要求所有 seq_cst 操作进入单一全局序。
