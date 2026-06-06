---
qid: cpp-cf-m-001
type: multi
kp: [cpp-control-flow]
difficulty: easy
answer_key: [B, D]
---

下列哪些循环结构**保证至少执行一次循环体**？（选择所有正确项）

A. `for` 循环（条件初始为 `false`）
B. `do-while` 循环
C. `while` 循环（条件初始为 `false`）
D. `do { ... } while(true);`

## Explanation

正确答案为 B、D。A项“`for` 循环（条件初始为 `false`）”不是正确项；B项“`do-while` 循环”是正确项；C项“`while` 循环（条件初始为 `false`）”不是正确项；D项“`do { ... } while(true);`”是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
