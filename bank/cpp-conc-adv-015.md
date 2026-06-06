---
qid: cpp-conc-adv-015
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

为什么 `memory_order_seq_cst` 是最安全但开销最大的内存序？

A. 它要求处理器和编译器维护一个全局一致的操作顺序，所有线程看到的原子操作序列相同，这通常需要额外的内存屏障指令，在多核架构上代价较高
B. 它会禁用 CPU 的乱序执行（OOO），导致整个程序串行化
C. 它每次操作都需要加互斥锁，比其他内存序多一次系统调用
D. 它会在每次原子操作后刷新整个 CPU 缓存，导致缓存命中率下降
