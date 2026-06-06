---
qid: cpp-friend-002
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: C
---

关于 `friend` 声明的位置，下列说法正确的是？

A. `friend` 声明必须放在 `public` 区域，否则编译报错
B. `friend` 声明必须放在 `private` 区域才有效
C. `friend` 声明放在 `public`、`protected`、`private` 任意区域效果相同
D. `friend` 声明只能放在类的最开头

## 解析

正确答案是 C，对应“friend 声明放在 public、protected、private 任意区域效果相同”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“friend 声明必须放在 public 区域，否则编译报错”不满足题干要求；B 项“friend 声明必须放在 private 区域才有效”不满足题干要求；D 项“friend 声明只能放在类的最开头”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
