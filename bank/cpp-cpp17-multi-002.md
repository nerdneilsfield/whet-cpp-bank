---
qid: cpp-cpp17-multi-002
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, D]
---
关于 `if constexpr` 的行为，**哪些说法是正确的**？（多选）

A. `if constexpr` 在编译期评估条件，未被选中的分支不会实例化。
B. `if constexpr` 只能用于 `constexpr` 数组或字面量。
C. `if constexpr` 可用于任何函数体，条件是常数表达式。
D. 在模板中，`if constexpr` 可避免被丢弃分支的模板实例化错误。

---

**解析：**

A 正确：被丢弃的分支不会被实例化（但仍会被语法检查）。
B 错误：条件是任何 `bool` 类型的常量表达式即可。
C 错误：`if constexpr` 只允许在模板上下文中（否则等价于普通 `if`）。
D 正确：这是 `if constexpr` 的主要用途之一（如替代 SFINAE 或部分特化）。