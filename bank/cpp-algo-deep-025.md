---
qid: cpp-algo-deep-025
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码用 `std::sort` 与 `std::lower_bound` 配合，但行为不一致，原因是？

```cpp
std::vector<int> v{5,2,8,1,9,3};
auto cmp = [](int a, int b){ return std::abs(a) < std::abs(b); };
std::sort(v.begin(), v.end(), cmp);
auto it = std::lower_bound(v.begin(), v.end(), 4);  // ← 默认 < 比较
```

A. `lower_bound` 不支持 lambda
B. `lower_bound` 必须使用**与排序时相同的比较器**，否则结果未定义
C. `std::sort` 不能用 lambda
D. `std::abs` 不能用于 int

## Explanation

正确答案是 B：二分搜索族要求范围已经按同一个比较器排序或至少满足对应分区条件。这里 sort 使用 abs 比较器，lower_bound 却使用默认 <，算法前提被破坏，结果不可靠。正确做法是 lower_bound 也传入同一个 cmp，并让 value 的比较语义一致。
