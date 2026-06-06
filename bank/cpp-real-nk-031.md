---
qid: cpp-real-nk-031
type: single
kp: [cpp-concurrency, cpp-cpp11]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: C
tags: [interview-real, bytedance]
---

`std::atomic` 的 `memory_order` 6 种语义中，**最严格**的是：

A. `memory_order_relaxed`
B. `memory_order_acquire`
C. **`memory_order_seq_cst`**
D. `memory_order_release`

---

**解析：**

C++11 atomic 的 6 种 memory_order，按"严格程度"递增大致：

1. **`relaxed`**：只保证原子性，不保证顺序。仅用于计数器（如 shared_ptr 引用计数 increment）
2. **`consume`**：依赖排序（实践中大多编译器实现为 acquire，已弃用建议）
3. **`acquire`**：所有后续读写不能重排到本操作之前（用于 load）
4. **`release`**：所有先前读写不能重排到本操作之后（用于 store）
5. **`acq_rel`**：同时具备 acquire 和 release 语义（用于 RMW 操作如 fetch_add）
6. **`seq_cst`**：顺序一致，全局所有线程看到所有 seq_cst 操作的顺序一致。**最严格**，开销最大，是默认值

常用组合：
- Release-Acquire 配对：生产者 store(release) + 消费者 load(acquire)，实现锁释放/获取语义
- seq_cst 用于需要全局顺序的场景（如 Dekker 算法），但慢

x86 上 acquire/release 几乎是免费的（强内存模型），但 seq_cst 需要 mfence。ARM 上各种 order 开销差异显著。

**来源：** 字节并发面试题 / cppreference memory_order