---
qid: cpp-iter-004
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: D
---

对于容器 `v`，`v.begin()` 和 `v.end()` 构成的区间是哪种形式？

A. 闭区间 `[begin, end]`
B. 开区间 `(begin, end)`
C. 左开右闭 `(begin, end]`
D. 左闭右开 `[begin, end)`

## Explanation

正确答案是 D，对应“左闭右开 [begin, end)”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“闭区间 [begin, end]”不满足题干要求；B 项“开区间 (begin, end)”不满足题干要求；C 项“左开右闭 (begin, end]”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
