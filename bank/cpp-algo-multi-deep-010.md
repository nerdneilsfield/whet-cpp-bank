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

---

**解析：**

- A ✅、B ✅：空范围的逻辑量化默认值（vacuous）。
- C ❌：返回的是 `last`（即 `end`），**不是 nullptr**。调用方必须用 `it == v.end()` 检查，**不要解引用**。
- D ✅：accumulate / reduce / inner_product 对空范围返回初值；transform / for_each / copy 等对空范围是空操作（no-op）。

边界条件意识对算法正确使用至关重要，尤其在范围由其他算法（如 `lower_bound`）的返回值切出来时，常出现空区间。
