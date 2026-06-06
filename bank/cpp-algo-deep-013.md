---
qid: cpp-algo-deep-013
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

统计 `v` 中正数的个数，下列哪种写法**最直接**且语义最清晰？

```cpp
std::vector<int> v{-2, 1, 3, -4, 5, 6};
???
```

A. `std::accumulate(v.begin(), v.end(), 0);`
B. `std::count_if(v.begin(), v.end(), [](int x){return x > 0;});`
C. `std::accumulate(v.begin(), v.end(), 0, [](int s, int x){return x > 0 ? s+x : s;});`
D. `std::find_if(v.begin(), v.end(), [](int x){return x > 0;}) - v.begin();`

## 解析

正确答案是 B：std::count_if 直接统计满足谓词 x > 0 的元素个数，语义最清楚。accumulate 默认求和，不是计数；若用它计数也要写成满足条件时 s+1，表达反而绕。find_if 只能找到第一个正数的位置，不能给出所有正数的总数。
