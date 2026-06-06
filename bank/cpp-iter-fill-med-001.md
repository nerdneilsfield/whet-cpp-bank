---
qid: cpp-iter-fill-med-001
type: fill
kp: [cpp-iterators]
difficulty: medium
answer_key: "base"
---
反向迭代器的成员函数返回对应正向迭代器: ___。

---

**解析：**

`reverse_iterator::base()` 返回其对应的底层正向迭代器。注意反向迭代器和 `base()` 返回的正向迭代器之间存在偏移关系：若 `ri` 指向元素 `i`，则 `ri.base()` 指向 `i` 的下一个元素。这种设计使得 `(++ri).base() == ri.base() - 1` 成立，确保反向迭代器的范围语义正确。