---
qid: cpp-cpp17-med-003
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: C
---

C++17 `std::optional<T>` 的 `value()` 与 `has_value()`+`operator*` 在语义上有重要差异。以下哪条表述**正确**？

A. `has_value()` 返回 `false` 时，`operator*` 返回默认构造的 `T` 对象
B. `value()` 和 `operator*` 功能完全等价，性能也一样
C. `has_value()` 返回 `false` 时调用 `value()` 抛出 `std::bad_optional_access`，而 `operator*` 是未定义行为
D. `value_or()` 比 `value()` 慢，因为总会构造 `T`

---

**解析：**

`std::optional` 的设计意图明确区分了"检查后访问"和"确信式访问"：

- `operator*()` / `operator->()`：**不检查**是否含值，空时调用是 UB（类似裸指针解引用）。要求调用者已经通过 `has_value()` 或 `operator bool()` 确认有值。
- `value()`：**运行时检查**，空时抛出 `std::bad_optional_access`。性能略差（分支 + 异常路径），但提供异常安全。
- `value_or(U&&)`：空时返回备选值，不会默认构造空 `T`——传引用或移动即可，不必然慢。

选项 A 错在 `operator*` 在空时是 UB；B 错在语义不等价；D 错在 `value_or` 不会额外构造 `T`。