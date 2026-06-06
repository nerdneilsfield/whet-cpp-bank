---
qid: cpp-algo-fill-deep-007
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["O(log n)", "logarithmic", "对数"]
---

`std::set<int>` 的成员函数 `find(key)` 的时间复杂度是 _______（请以大 O 记号给出）。

## Explanation

答案是 O(log n)。std::set 通常由平衡二叉搜索树实现，成员函数 find 能利用树的有序结构沿路径查找。注意这是容器成员函数的复杂度；通用算法 std::find 只是线性遍历迭代器范围，仍是 O(n)，不会自动变成树查找。
