---
qid: cpp-poly-multi-002
type: multi
kp: [cpp-polymorphism]
difficulty: medium
answer_key: [A, C, D]
---
关于 `override` 与 `final` 的语义，**哪些说法是正确的**？（多选）

A. `final` 用于成员函数表示该虚函数不能再被进一步覆盖。
B. `override` 用于类表示该类是最终类。
C. `final` 用于类表示该类不能被继承。
D. 一个函数可以同时声明 `override final`。

---

**解析：**

A 正确：成员函数后的 `final` 阻止派生类继续覆盖。
B 错误：表示「最终类」的是 `final`，不是 `override`。
C 正确：类后的 `final` 表示禁止派生。
D 正确：合法且常见，表示「确实覆盖且禁止再被覆盖」。