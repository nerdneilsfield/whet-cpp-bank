---
qid: cpp-algo-multi-deep-010
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: [A, B, D]
---

关于"对空范围调用"算法的行为，下列哪些**正确**？（多选）

A. `std::all_of(empty)` 返回 `true`（vacuous truth）
B. `std::any_of(empty)` 返回 `false`
C. `std::min_element(empty)` 返回 `nullptr`
D. `std::accumulate(first, first, init)` 返回 `init`

## 解析

正确选项是 A、B、D。空范围上 all_of 为 true、any_of 为 false，这是逻辑量化的默认值；accumulate(first, first, init) 直接返回 init。min_element 找不到时返回 last/end，不是 nullptr，也不能解引用。
