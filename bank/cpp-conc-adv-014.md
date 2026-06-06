---
qid: cpp-conc-adv-014
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: release（写端）配对 acquire（读端）；release 写操作之前的所有内存操作对执行 acquire 读操作的线程可见
---

`memory_order_release` 与 `memory_order_acquire` 配对使用时：写端使用 ______，读端使用 ______，从而保证写端在 release 之前的所有内存写入，对读端在 acquire 之后可见。
