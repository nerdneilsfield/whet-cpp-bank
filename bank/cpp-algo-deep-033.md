---
qid: cpp-algo-deep-033
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

C++17 `std::reduce` 与 `std::accumulate` 的**关键区别**是？

```cpp
std::vector<int> v{1,2,3,4,5};
auto a = std::accumulate(v.begin(), v.end(), 0);  // 严格左折叠
auto r = std::reduce(v.begin(), v.end(), 0);      // ?
```

A. 完全相同，`reduce` 只是新名字
B. `reduce` 允许**任意求值顺序与重排**，要求二元操作满足**结合律与交换律**；可加 `std::execution::par` 并行
C. `reduce` 更慢，只在并行库中存在
D. `reduce` 不接受初值

## Explanation

正确答案是 B：accumulate 是固定顺序的左折叠，而 reduce 允许重排求值顺序，因此可并行。reduce 的二元操作需要满足结合律，实际并行归约通常还依赖交换性。浮点加法会因重排产生不同舍入结果，这是 reduce 的常见风险。
