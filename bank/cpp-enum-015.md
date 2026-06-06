---
qid: cpp-enum-015
type: multi
kp: [cpp-enum]
difficulty: easy
answer_key: [A, C]
---
关于 `enum class`，以下哪些说法正确？（多选）

A. 枚举器必须通过 `枚举名::枚举器` 方式访问
B. 枚举器可隐式转换为 `int`，无需 cast
C. 可以通过 `enum class E : short` 指定底层存储类型
D. 传统 `enum` 和 `enum class` 的枚举器都注入外层命名空间

## 解析

正确答案是 A、C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 A 正确：枚举器必须通过 ｀枚举名::枚举器｀ 方式访问；B 错误：枚举器可隐式转换为 ｀int｀，无需 cast；C 正确：可以通过 ｀enum class E : short｀ 指定底层存储类型；D 错误：传统 ｀enum｀ 和 ｀enum class｀ 的枚举器都注入外层命名空间。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
