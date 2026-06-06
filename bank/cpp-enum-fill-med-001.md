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

## Explanation

应填 `class`。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
