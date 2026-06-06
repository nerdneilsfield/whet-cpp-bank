---
qid: cpp-algo-deep-029
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码的输出是？

```cpp
std::vector<int> v{1, 2, 3, 4};
auto sum1 = std::accumulate(v.begin(), v.end(), 0);     // init=0 (int)
auto sum2 = std::accumulate(v.begin(), v.end(), 0.5);   // init=0.5 (double)
std::cout << sum1 << " " << sum2;
```

A. `10 10.5`，但 `sum1` 类型是 `double`
B. `10 10.5`，`sum1` 类型是 `int`（由初始值类型决定）
C. `10 10`，两者都截断为 int
D. `10.5 10.5`

## 解析

正确答案是 B：std::accumulate 的累加器类型由初始值 init 的类型决定。sum1 使用 int 初值 0，所以类型是 int；sum2 使用 double 初值 0.5，所以得到 10.5。常见误区是在 vector<double> 上传 0，导致精度被截断。
