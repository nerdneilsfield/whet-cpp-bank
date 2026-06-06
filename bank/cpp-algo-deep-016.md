---
qid: cpp-algo-deep-016
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码 `std::mismatch` 的返回类型是？

```cpp
std::vector<int> a{1, 2, 3, 4};
std::vector<int> b{1, 2, 9, 4};
auto r = std::mismatch(a.begin(), a.end(), b.begin());
// 输出 r 的相关信息
```

A. `int`，等于第一个不匹配位置的下标
B. `bool`，是否完全相等
C. `std::pair<iterator, iterator>`，分别指向两序列第一次不相等处
D. `std::vector<int>`，所有不匹配的元素

## Explanation

正确答案是 C：std::mismatch 返回一对迭代器，分别指向两个序列第一次不相等的位置。本例会指向 a[2] 的 3 和 b[2] 的 9。误区是把 mismatch 当作返回 bool 或下标的算法；若全相等，返回位置会到达相应末尾。
