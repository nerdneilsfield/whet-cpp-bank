---
qid: cpp-cf-m-004
type: multi
kp: [cpp-control-flow]
difficulty: easy
answer_key: [A, B, D]
---

下列哪些是**合法的无限循环**写法？（选择所有正确项）

A. `for (;;) { ... }`
B. `while (true) { ... }`
C. `for (int i = 0; i < 10; i++) { ... }`
D. `do { ... } while (1);`

## 解析

正确答案为 A、B、D。A项“`for (;;) { ... }`”是正确项；B项“`while (true) { ... }`”是正确项；C项“`for (int i = 0; i < 10; i++) { ... }`”不是正确项；D项“`do { ... } while (1);`”是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
