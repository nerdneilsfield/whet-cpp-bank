---
qid: cpp-algo-multi-001
type: multi
kp: [cpp-algorithms]
difficulty: medium
answer_key: [A, B, C]
---
关于 `<algorithm>` 中算法对迭代器类别的要求，**哪些说法是正确的**？（多选）

A. `std::sort` 要求随机访问迭代器（RandomAccessIterator）。
B. `std::find` 仅要求输入迭代器（InputIterator）。
C. `std::reverse` 要求双向迭代器（BidirectionalIterator）。
D. `std::lower_bound` 要求双向迭代器即可。

---

**解析：**

A 正确：`sort` 需要随机访问以做分区。
B 正确：`find` 只需顺序遍历。
C 正确：`reverse` 需要从两端反向交换。
D 错误：`lower_bound` 要求至少 ForwardIterator，但若想 O(log n) 则需要随机访问；双向迭代器不是其要求关键，本题表述「双向迭代器即可」不准确——需 ForwardIterator，并在 RandomAccess 时为 O(log n)。

## 解析

正确答案为 A、B、C。A项“`std::sort` 要求随机访问迭代器（RandomAccessIterator）。”是正确项；B项“`std::find` 仅要求输入迭代器（InputIterator）。”是正确项；C项“`std::reverse` 要求双向迭代器（BidirectionalIterator）。”是正确项；D项“`std::lower_bound` 要求双向迭代器即可。”不是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
