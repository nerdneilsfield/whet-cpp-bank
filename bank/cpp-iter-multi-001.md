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