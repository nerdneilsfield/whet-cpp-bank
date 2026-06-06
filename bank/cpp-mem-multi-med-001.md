---
qid: cpp-mem-multi-med-001
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, C]
---
以下关于 `std::shared_ptr` 的说法，**哪些是正确的**？（多选）

A. `shared_ptr` 的引用计数操作是原子的（线程安全的引用计数）
B. `shared_ptr` 的解引用（`operator*`）是线程安全的，多线程可同时通过同一个 `shared_ptr` 读写指向的对象
C. 多个线程可以同时读取**不同** `shared_ptr` 副本所指向的同一对象，只要不修改
D. `shared_ptr` 的拷贝是免费的，没有性能开销

---

**解析：**

A 正确：libstdc++/libc++ 实现中引用计数使用 `std::atomic`，inc/dec 线程安全。
B 错误：原子的是引用计数，不是被指对象。多线程同时通过 `shared_ptr<T>` 写 `T` 仍是数据竞争。
C 正确：只读共享访问无需同步（前提：不修改 `T`）。
D 错误：每次拷贝需要原子 inc 引用计数（memory_order 至少是 relaxed 或无代价的 seq_cst），比裸指针拷贝慢约 10–100 倍。

## Explanation

A、C 正确：`shared_ptr` 的控制块引用计数更新是线程安全的，但这不等于被管理对象本身线程安全。多个副本只读访问同一对象通常没问题，写访问仍需额外同步。常见误区是把“共享所有权安全”误解成“共享对象读写安全”，并忽略拷贝时的原子计数开销。
