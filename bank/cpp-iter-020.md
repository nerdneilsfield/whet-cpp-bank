---
qid: cpp-iter-020
type: multi
kp: [cpp-iterators]
difficulty: easy
answer_key: [A, B, D]
---

以下哪些容器/适配器提供**双向迭代器**（但不是随机访问迭代器）？（多选）

A. `std::list`
B. `std::set`
C. `std::vector`
D. `std::map`
E. `std::unordered_map`

## 解析

本题正确答案是 A, B, D。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。A 项正确：“std::list”符合题干要求；B 项正确：“std::set”符合题干要求；C 项错误：“std::vector”与题干要求或 C++ 规则不符；D 项正确：“std::map E. std::unorderedmap”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
