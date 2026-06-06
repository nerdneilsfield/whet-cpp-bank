---
qid: cpp-enum-004
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---
传统 `enum` 与 `enum class` 的关键区别是？

A. `enum class` 允许重复枚举器名称
B. 传统 `enum` 不能指定底层类型
C. `enum class` 的枚举器不隐式转换为整数，访问须加作用域限定符
D. `enum class` 不支持 switch 语句

## 解析

正确答案是 C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 C 的表述“｀enum class｀ 的枚举器不隐式转换为整数，访问须加作用域限定符”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
