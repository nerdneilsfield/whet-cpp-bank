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
