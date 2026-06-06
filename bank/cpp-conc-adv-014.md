---
qid: cpp-conc-adv-014
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: release（写端）配对 acquire（读端）；release 写操作之前的所有内存操作对执行 acquire 读操作的线程可见
---

`memory_order_release` 与 `memory_order_acquire` 配对使用时：写端使用 ______，读端使用 ______，从而保证写端在 release 之前的所有内存写入，对读端在 acquire 之后可见。

## Explanation

应填 `release（写端）配对 acquire（读端）；release 写操作之前的所有内存操作对执行 acquire 读操作的线程可见`。release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
