---
qid: cpp-class-multi-004
type: multi
kp: [cpp-classes]
difficulty: medium
answer_key: [A, B, D]
---
关于 ODR-use（One Definition Rule 使用）的场景，**哪些说法是正确的**？（多选）

A. 取一个变量的地址会构成 ODR-use。
B. 将变量绑定到引用会构成 ODR-use。
C. 在 `sizeof` 操作数中使用变量会构成 ODR-use。
D. C++17 起，inline 变量可同时在多个 TU 中定义而不违反 ODR。

---

**解析：**

A 正确：取址要求实体存在，构成 ODR-use。
B 正确：引用绑定需要实际存储位置，构成 ODR-use。
C 错误：`sizeof` 是不求值操作数，不构成 ODR-use。
D 正确：C++17 引入 inline 变量，允许多 TU 中重复定义且合并为同一实体。