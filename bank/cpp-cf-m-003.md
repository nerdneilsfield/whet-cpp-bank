---
qid: cpp-cf-m-003
type: multi
kp: [cpp-control-flow]
difficulty: easy
answer_key: [A, C, D]
---

关于 `switch` 语句，下列哪些说法**正确**？（选择所有正确项）

A. 每个 `case` 标签末尾若没有 `break`，程序会继续执行下一个 `case` 的语句（fall-through）
B. `switch` 的条件表达式可以是浮点型（`double`）
C. `default` 分支不是必须的，可以省略
D. 多个 `case` 标签可以共用同一段代码体

## 解析

正确答案是 A、C、D。`switch` 中缺少 `break` 会发生 fall-through，`default` 可以省略，多个 `case` 标签也可以共享一段语句。`switch` 条件不能是浮点型，只能是整型、枚举型或可转换到这些类型的表达式。
