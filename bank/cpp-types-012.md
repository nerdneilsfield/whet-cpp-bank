---
qid: cpp-types-012
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---
以下哪个声明使用了**类型别名**（`using` 语法）？

A. `typedef int MyInt;`
B. `using MyInt = int;`
C. `#define MyInt int`
D. `auto MyInt = int{};`

## 解析

正确答案是 B，即 `using MyInt = int;`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
