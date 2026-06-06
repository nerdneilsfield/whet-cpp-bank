---
qid: cpp-algo-fill-deep-002
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::lower_bound", "lower_bound", "std::ranges::lower_bound"]
---

在已升序排好的 `std::vector<int> v` 中，要找到**不小于** `value` 的第一个元素位置（即可插入位置左边界），应使用 STL 算法 _______。

## 解析

答案是 std::lower_bound。它在已排序范围内返回第一个不小于 value 的位置，也就是保持有序插入时的左边界。与 find 不同，它利用有序前提进行二分查找；误区是忘记输入必须按相同比较器排序，否则返回位置没有可靠含义，甚至会误判插入点。
