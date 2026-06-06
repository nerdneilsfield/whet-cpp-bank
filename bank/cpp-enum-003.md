---
qid: cpp-enum-003
type: fill
kp: [cpp-enum]
difficulty: easy
answer_key: "Color::Red"
---
`enum class Color { Red, Green, Blue };` 声明后，访问 `Red` 的正确写法是（填完整表达式）：

___

## 解析

应填 `Color::Red`。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
