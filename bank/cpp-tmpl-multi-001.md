---
qid: cpp-tmpl-multi-001
type: multi
kp: [cpp-templates]
difficulty: medium
answer_key: [A, B, D]
---
关于 SFINAE（Substitution Failure Is Not An Error）的适用范围，**哪些说法是正确的**？（多选）

A. SFINAE 只对模板参数推导/替换阶段的「立即上下文」错误生效。
B. 函数体内的错误不属于 SFINAE，会直接报错。
C. SFINAE 可以使用 `static_assert` 来排除候选重载。
D. `std::enable_if` 与 `void_t` 都是 SFINAE 技巧的常用工具。

---

**解析：**

A 正确：仅在立即上下文（如返回类型、模板形参、默认实参等）中的替换失败被静默忽略。
B 正确：函数体属于非立即上下文，替换失败/错误会变成硬错误。
C 错误：`static_assert` 一旦触发就是硬错误，不能作为 SFINAE 工具。
D 正确：两者均是 SFINAE 的经典工具。

## 解析

正确选项是 A（SFINAE 只对模板参数推导/替换阶段的「立即上下文」错误生效。）、B（函数体内的错误不属于 SFINAE，会直接报错。）、D（`std::enable_if` 与 `void_t` 都是 SFINAE 技巧的常用工具。），它们符合本题涉及的 C++ 规则。C（SFINAE 可以使用 `static_assert` 来排除候选重载。） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
