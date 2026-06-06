---
qid: cpp-stl-008
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

要使用 `std::vector`，需要包含哪个头文件？

A. `#include <vector>`
B. `#include <array>`
C. `#include <list>`
D. `#include <iostream>`

## 解析

正确答案是 A，即 `#include <vector>`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
