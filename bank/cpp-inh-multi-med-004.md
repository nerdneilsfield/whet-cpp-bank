---
qid: cpp-inh-multi-med-004
type: multi
kp: [cpp-inheritance]
difficulty: medium
answer_key: [A, B, D]
---
关于 `override` 关键字的效果，**哪些说法是正确的**？（多选）

A. `override` 让编译器检查该函数是否确实覆盖了基类虚函数。
B. 若基类虚函数签名不匹配，使用 `override` 会编译失败。
C. `override` 改变函数的虚分派机制。
D. `override` 是上下文敏感关键字，仅在成员函数声明位置具有特殊含义。

---

**解析：**

A 正确：核心目的是在编译期捕获意外的「未覆盖」错误。
B 正确：签名不匹配（如多了 const、参数类型不同）时编译器报错。
C 错误：`override` 不改变语义，仅提供静态检查。
D 正确：它是上下文相关的标识符，普通位置可作普通名字。