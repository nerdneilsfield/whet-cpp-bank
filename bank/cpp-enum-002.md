---
qid: cpp-enum-002
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下哪个关键字用于声明有作用域的枚举（scoped enum）？

A. `enum`
B. `enum class`
C. `enum struct` 是唯一方式
D. `scoped_enum`

## Explanation

正确答案是 B。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 B 的表述“｀enum class｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
