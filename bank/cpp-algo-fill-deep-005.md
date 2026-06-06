---
qid: cpp-algo-fill-deep-005
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::stable_partition", "stable_partition", "std::ranges::stable_partition"]
---

要按谓词把容器划分为两部分，并**保持每部分中元素的相对顺序**，应使用算法 _______。

## 解析

答案是 std::stable_partition。它按谓词把满足条件的元素和不满足条件的元素划分为两段，并保持每段内部原有相对顺序。std::partition 也能划分，通常可更快或少用额外空间，但不保证稳定性，所以不能满足题目强调的“保序”要求。
