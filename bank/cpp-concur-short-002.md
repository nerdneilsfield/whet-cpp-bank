---
qid: cpp-concur-short-002
type: short
kp: [cpp-concurrency]
difficulty: medium
rubric:
  - 区分 memory_order 枚举（relaxed / consume / acquire / release / acq_rel / seq_cst）
  - 解释 acquire 语义：保证之后读不重排到 acquire 之前
  - 解释 release 语义：保证之前写不重排到 release 之后
  - 指出 seq_cst 是全序同步但性能代价最大
  - 提到错误 memory order 可能引入 data race
---
请解释 C++ atomic 中的 memory order 是什么，简述 acquire/release 语义的区别。

---

**参考答案：**

memory order 控制原子操作的内存同步范围，决定该操作对其他线程的可见性。`memory_order_acquire` 用于加载操作，保证本线程后续的读取不会重排到 acquire 之前；`memory_order_release` 用于存储操作，保证本线程之前的写入不会重排到 release 之后；`memory_order_seq_cst` 是默认值，在 acquire-release 基础上额外保证全序（所有线程看到的一致顺序），但性能代价最大。不同线程通过 acquire-release 配对可以建立一种 happens-before 关系，若选错 order 则无法保证同步、可能产生 data race。

## 解析

release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。 本题短答应围绕核心概念展开：memory order 控制原子操作的内存同步范围，决定该操作对其他线程的可见性。｀memory_order_acquire｀ 用于加载操作，保证本线程后续的读取不会重排到 acquire 之前；｀memory_order_release｀ 用于存储操作，保证本线程之前的写入不会重排到 release 之后；｀memory_order_seq_cst｀ 是默认值，在 acquire-release 基础上额外保证全序（所有线程看到的一致顺序），但性能代价最大。不同线程通过 acquire-release 配对可以 评分重点包括：区分 memory_order 枚举（relaxed / consume / acquire / release / acq_rel / seq_cst）；解释 acquire 语义：保证之后读不重排到 acquire 之前；解释 release 语义：保证之前写不重排到 release 之后。常见误区是只给出结论、不说明机制，或忽略异常路径、同步边界、生命周期等限制条件。
