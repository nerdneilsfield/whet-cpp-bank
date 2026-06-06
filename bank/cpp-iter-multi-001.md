---
qid: cpp-iter-multi-001
type: multi
kp: [cpp-iterators]
difficulty: medium
answer_key: [A, C, D]
---
关于迭代器类别的能力，**哪些说法是正确的**？（多选）

A. RandomAccessIterator 支持 `it + n`、`it1 - it2`、`it[n]`。
B. ForwardIterator 支持 `--it`。
C. InputIterator 只能单向遍历一次（可能不支持再读取）。
D. 所有 BidirectionalIterator 也必然是 ForwardIterator。

---

**解析：**

A 正确：随机访问迭代器的全部能力。
B 错误：BidirectionalIterator 才支持 `--it`，ForwardIterator 仅单向。
C 正确：InputIterator 可单次读取；再读取可能无效（如流迭代器）。
D 正确：BidirectionalIterator 是 ForwardIterator 的超集。

## 解析

本题正确答案是 A, C, D。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。A 项正确：“RandomAccessIterator 支持 it + n、it1 - it2、it[n]。”符合题干要求；B 项错误：“ForwardIterator 支持 --it。”与题干要求或 C++ 规则不符；C 项正确：“InputIterator 只能单向遍历一次（可能不支持再读取）。”符合题干要求；D 项正确：“所有 BidirectionalIterator 也必然是 ForwardIterator。”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
