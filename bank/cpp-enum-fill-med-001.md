---
qid: cpp-enum-fill-med-001
type: fill
kp: [cpp-enum]
difficulty: medium
answer_key: "class"
---
强类型枚举关键字 `enum ___`。

---

**解析：**

`enum class`（也称 scoped enumeration）是 C++11 引入的强类型枚举，枚举值不会隐式转换为整型，且枚举名必须在作用域内（需 `EnumType::Value` 访问）。底层类型默认是 `int`，但可显式指定。它解决了传统 `enum` 的名称污染和隐式转换问题。