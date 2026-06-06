---
qid: cpp-algo-deep-039
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::includes` 判断 `a ⊇ b`，结果是？

```cpp
std::vector<int> a{1,2,3,4,5,6};
std::vector<int> b{2,4,6};
bool r = std::includes(a.begin(), a.end(), b.begin(), b.end());
std::cout << r;
```

A. `0`，因为 `b` 不是 `a` 的连续子序列
B. `1`，因为元素之和相同
C. `1`，`a` 包含 `b` 的所有元素（按有序集合包含语义，要求两端都已排序）
D. UB，需要 `std::set`

## 解析

正确答案是 C：std::includes 判断第二个有序范围是否是第一个有序范围的子集。b 的 2、4、6 都出现在 a 中，因此返回 true，并不要求这些元素在 a 中连续出现。误区是把 includes 当成子串搜索；未排序输入也会破坏算法前提。
