---
qid: cpp-tmpl-005
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 类模板实例化语法

已有 `template<typename T> class Stack { ... };`，下列哪种实例化方式正确？

A. `Stack s<int>;`
B. `Stack<int> s;`
C. `Stack s = Stack(int);`
D. `Stack<> s(int);`

## Explanation

正确答案是 B，即 `Stack<int> s;`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
