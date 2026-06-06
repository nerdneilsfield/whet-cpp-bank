---
qid: cpp-algo-deep-032
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

`std::iota` 的作用是？

```cpp
std::vector<int> v(5);
std::iota(v.begin(), v.end(), 10);
// v = ?
```

A. `10 10 10 10 10`
B. `10 11 12 13 14`
C. `0 1 2 3 4`
D. 把 v 反转

## 解析

正确答案是 B：std::iota 会从给定初值开始逐个写入，并在每次写入后自增，所以得到 10 11 12 13 14。它不是把同一值填满整个范围，填同一值应使用 fill。iota 位于 <numeric>，常用于生成连续下标、序号或 ID。
