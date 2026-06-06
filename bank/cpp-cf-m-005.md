---
qid: cpp-cf-m-005
type: multi
kp: [cpp-control-flow]
difficulty: easy
answer_key: [A, C]
---

关于 `break` 和 `continue`，下列哪些说法**正确**？（选择所有正确项）

A. `break` 只跳出它所在的**最内层**循环或 `switch`，不会跳出外层循环
B. `continue` 会终止整个循环，跳到循环后面的语句
C. `continue` 跳过当前迭代剩余的语句，直接进入下一次迭代的条件判断
D. 在 `switch` 内使用 `continue` 可以跳出 `switch`

## Explanation

正确答案为 A、C。A项“`break` 只跳出它所在的**最内层**循环或 `switch`，不会跳出外层循环”是正确项；B项“`continue` 会终止整个循环，跳到循环后面的语句”不是正确项；C项“`continue` 跳过当前迭代剩余的语句，直接进入下一次迭代的条件判断”是正确项；D项“在 `switch` 内使用 `continue` 可以跳出 `switch`”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
