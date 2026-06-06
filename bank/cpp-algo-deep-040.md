---
qid: cpp-algo-deep-040
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列代码（C++17）使用执行策略并行求和，**风险**是？

```cpp
std::vector<int> v(1'000'000, 1);
long long sum = 0;
std::for_each(std::execution::par, v.begin(), v.end(),
              [&](int x){ sum += x; });
std::cout << sum;
```

A. 安全；`for_each` 自动加锁
B. 编译错误
C. **数据竞争（data race）**，对 `sum` 的并发非原子写是 UB；正确做法是用 `std::reduce`
D. 输出固定为 0

## Explanation

正确答案是 C：execution::par 允许多个调用并发执行，但不会自动同步捕获变量。多个线程同时执行 sum += x 是对同一变量的非原子读改写，形成数据竞争，行为未定义。并行求和应使用 std::reduce 或 transform_reduce，而不是在 for_each 中共享累加器。
