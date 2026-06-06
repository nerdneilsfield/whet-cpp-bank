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

---

**解析：**

- A ❌：仅 accumulate 顺序确定；reduce 顺序未指定。
- B ✅：accumulate 总按 `((((init+v0)+v1)+v2)+...)`，浮点结果可复现。
- C ✅：reduce 可重排，因此 binary_op 必须结合；多线程实现还要求局部归约可任意排列（交换律），可加 `std::execution::par` 等策略。
- D ❌：完全不同；reduce 引入了"可并行"的契约。

并行加和首选 `std::reduce(std::execution::par, ..., 0.0)`；要可复现的浮点求和用 accumulate 或 Kahan 算法。
