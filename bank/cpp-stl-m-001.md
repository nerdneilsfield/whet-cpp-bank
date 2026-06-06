---
qid: cpp-stl-m-001
type: multi
kp: [cpp-stl-basics]
difficulty: easy
answer_key: [A, B, D]
---

下列哪些是 `std::vector` 的合法成员函数？（选择所有正确项）

A. `push_back()`
B. `size()`
C. `insert_front()`
D. `empty()`

## 解析

正确选项是 A（`push_back()`）、B（`size()`）、D（`empty()`），它们符合本题涉及的 C++ 规则。C（`insert_front()`） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
