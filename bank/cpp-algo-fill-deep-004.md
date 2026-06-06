---
qid: cpp-algo-fill-deep-004
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["O(n)", "Θ(n)", "线性", "linear"]
---

`std::nth_element(first, nth, last)` 在平均情况下的时间复杂度是 _______（请以大 O 记号或汉字描述给出答案）。

## Explanation

答案是 O(n) 或线性。nth_element 只保证 nth 位置放上按排序后应在该位置的元素，并让两侧满足分区关系，但两侧内部都不排序。因此它平均复杂度优于完整 sort，适合只关心第 k 小或前若干候选的场景。误区是把它当成排序算法，期待整个范围有序。
