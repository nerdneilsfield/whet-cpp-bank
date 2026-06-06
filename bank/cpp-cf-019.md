---
qid: cpp-cf-019
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: D
---

以下哪种写法表示一个无限循环？

A. `for (int i = 0; i != 0; i++)`
B. `while (false) { }`
C. `for (int i = 0; i < 1; i--)`
D. `for (;;) { }`

## Explanation

正确答案为 D，因为“`for (;;) { }`”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
