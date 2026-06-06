---
qid: cpp-enum-017
type: multi
kp: [cpp-enum]
difficulty: easy
answer_key: [B, D]
---
以下哪些代码片段会导致编译错误？（多选）

A. `enum Color { Red, Green }; int x = Red;`
B. `enum class Color { Red, Green }; int x = Color::Red;`
C. `enum class Color { Red, Green }; Color c = Color::Red;`
D. `enum class Color { Red }; if (Color::Red == 0) {}`

## Explanation

正确答案是 B、D。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。 A 错误：｀enum Color { Red, Green }; int x = Red;｀；B 正确：｀enum class Color { Red, Green }; int x = Color::Red;｀；C 错误：｀enum class Color { Red, Green }; Color c = Color::Red;｀；D 正确：｀enum class Color { Red }; if (Color::Red == 0) {}｀。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
