---
qid: cpp-algo-multi-deep-006
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [B, C]
---

关于 `std::accumulate` 与 `std::reduce`，下列哪些**正确**？（多选）

A. 两者都允许任意求值顺序，结果总是确定
B. `std::accumulate` 是严格左折叠，结果对**浮点求和**确定可复现
C. `std::reduce` 要求 binary_op 满足结合律（典型实现还假定交换律），可并行
D. `std::reduce` 是 `std::accumulate` 的别名

## 解析

正确选项是 B、C。accumulate 是严格左折叠，因此浮点求和顺序固定，虽然有舍入误差但结果可复现。reduce 允许重排以支持并行，所以要求操作满足结合律，实际实现还常依赖交换性。它不是 accumulate 的别名，结果顺序语义不同。
