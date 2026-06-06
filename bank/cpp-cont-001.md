---
qid: cpp-cont-001
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

`std::map` 中查找一个键的时间复杂度是？

A. O(1)
B. O(log n)
C. O(n)
D. O(n log n)

## Explanation

正确答案是 B。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。选项 B 的表述“O(log n)”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
