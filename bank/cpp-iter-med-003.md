---
qid: cpp-iter-med-003
type: single
kp: [cpp-iterators]
difficulty: medium
answer_key: C
---

input iterator 与 forward iterator 最关键的区别是？

A. forward iterator 支持随机访问 `it[n]`，input iterator 不支持
B. input iterator 只能读不能写，forward iterator 可以写
C. input iterator 是**单趟**（single-pass）的，对同一序列再走一遍无定义；forward iterator 是**多趟**（multi-pass）的，可以重复遍历
D. input iterator 不支持 `++`，forward iterator 支持

---

**解析：**

C++ 迭代器分类的核心差异常被误解。逐项澄清：

- **A 错**：随机访问是 random-access iterator 的能力，forward iterator 不支持 `it[n]` 也不支持 `it + n`。
- **B 错**：可读可写跟 input/output/forward 是正交维度。`std::istream_iterator` 是 input iterator，只能读；但 `forward_iterator` 既可以是 const 也可以是 mutable（如 `std::forward_list::iterator`），不是 forward 就一定可写。
- **D 错**：input iterator 也支持 `++`，所有迭代器都至少支持前进。
- **C 对**：input iterator 的"单趟"语义来源于它的典型实现是流（`istream_iterator`、`istreambuf_iterator`）——读了就过去了，无法 rewind。所以 `for` 两次循环、或先 `std::distance(first, last)` 再遍历一次，对 input iterator 都是 UB。forward iterator 增加的本质能力就是"对同一段范围可以走多次，每次得到等价结果"。

这条差异决定了算法的复制语义：input iterator 只能保证 `++it` 后旧迭代器的拷贝失效，forward iterator 才能保证拷贝独立可用。

## 解析

正确答案是 C，对应“input iterator 是单趟（single-pass）的，对同一序列再走一遍无定义；forward iterator 是多趟（multi-pass）的，可以重复遍历”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“forward iterator 支持随机访问 it[n]，input iterator 不支持”不满足题干要求；B 项“input iterator 只能读不能写，forward iterator 可以写”不满足题干要求；D 项“input iterator 不支持 ++，forward iterator 支持”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
