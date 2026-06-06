---
qid: cpp-algo-004
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: D
---

`std::find` 在容器中查找某个值，若未找到，返回什么？

A. `nullptr`
B. `-1`
C. 容器的 `begin()` 迭代器
D. 容器的 `end()` 迭代器

## Explanation

正确答案是 D。`std::find(first, last, value)` 在半开区间 `[first, last)` 中线性查找；若没找到，就返回传入的 `last` 迭代器。对容器而言通常就是 `container.end()`，它不是有效元素，不能解引用。
