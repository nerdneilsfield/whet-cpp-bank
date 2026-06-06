---
qid: cpp-friend-008
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: B
---

若要让类 A 和类 B 互为友元（双向友元），需要？

A. 只需在 A 中声明 `friend class B;` 即可，自动双向生效
B. 分别在 A 中声明 `friend class B;`，在 B 中声明 `friend class A;`
C. 在任意一个公共基类中声明友元关系
D. C++ 不支持双向友元

## Explanation

正确答案是 B，对应“分别在 A 中声明 friend class B;，在 B 中声明 friend class A;”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“只需在 A 中声明 friend class B; 即可，自动双向生效”不满足题干要求；C 项“在任意一个公共基类中声明友元关系”不满足题干要求；D 项“C++ 不支持双向友元”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
