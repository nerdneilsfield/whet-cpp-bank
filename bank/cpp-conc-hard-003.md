---
qid: cpp-conc-hard-003
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

`std::memory_order_relaxed` 只保证原子性，不提供同步语义。以下哪种场景下使用 `relaxed` 是**安全且正确**的？

A. 两个线程通过一个 `atomic<bool>` 标志同步，生产者写 `true`，消费者等待 `true` 后读取共享缓冲区

B. 多线程并发修改一个链表，每个线程用 `relaxed` load 读取头节点后执行 CAS

C. 一个计数器只用于统计（如已处理请求数），多个线程以 `relaxed` 方式对其执行 `fetch_add`，最终在所有线程结束后主线程读取总数

D. 线程1用 `relaxed` store 写入数据地址指针，线程2用 `relaxed` load 读取该指针后解引用访问数据
