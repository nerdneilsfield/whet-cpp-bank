---
qid: cpp-cpp11-005
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: C
---

# 认知：enum class 作用域

下列关于 `enum class` 的说法，**正确**的是？

A. `enum class` 中的枚举值会隐式转换为 `int`
B. `enum class Color { Red };` 后可以直接写 `int x = Red;`
C. `enum class` 的枚举值必须通过作用域限定符访问，如 `Color::Red`
D. `enum class` 与普通 `enum` 的作用域规则完全相同

## 解析

正确答案是 C。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 C 的表述“｀enum class｀ 的枚举值必须通过作用域限定符访问，如 ｀Color::Red｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
