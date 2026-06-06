---
qid: cpp-cont-med-002
type: single
kp: [cpp-containers]
difficulty: medium
answer_key: B
---
关于 `std::unordered_map` 在大量哈希冲突时的复杂度，下列说法正确的是？

A. 查找始终是 O(1)，与哈希函数无关
B. 最坏情况下查找退化为 O(n)
C. 标准要求自动 rehash 解决冲突，因此不会退化
D. 退化为 O(log n)，因为内部用红黑树兜底

---

**解析：**

`std::unordered_map` 用开链法（separate chaining）实现哈希表，每个桶是一个链表（或类似的线性结构，标准不指定）。当哈希函数把大量 key 映射到同一个桶时，查找需要遍历整个桶内链表，最坏退化为 O(n)。标准并不要求“树化”（这是 Java 8 `HashMap` 的做法，C++ 标准没规定），rehash 只在负载因子超过阈值时发生，无法解决哈希函数本身的质量问题。攻击者可利用此构造哈希碰撞 DoS。

## 解析

正确答案是 B。`std::unordered_map` 基于哈希表，平均 O(1)，但严重冲突时可退化。选项 B 的表述“最坏情况下查找退化为 O(n)”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
