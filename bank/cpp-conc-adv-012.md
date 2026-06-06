---
qid: cpp-conc-adv-012
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: memory_order_seq_cst（顺序一致性）
---

`std::atomic` 操作的默认内存序是 ______，它提供最强的顺序保证，确保所有线程观察到的原子操作顺序一致。

## Explanation

应填 `memory_order_seq_cst（顺序一致性）`。`std::atomic` 保证单个对象的原子访问，但是否提供同步还取决于所用内存序。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
