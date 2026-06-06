---
qid: cpp-algo-fill-deep-008
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::execution::par_unseq", "par_unseq", "execution::par_unseq"]
---

C++17 在 `<execution>` 中提供 4 个执行策略：`seq`、`par`、`unseq`（C++20）、________。其中既允许多线程并行又允许同一线程内矢量化交错执行的策略是 ________（请填策略名，可带或不带命名空间限定）。

## 解析

答案是 std::execution::par_unseq。它同时允许线程级并行和向量化或交错执行，因此对用户函数限制最严，要求操作之间不能有顺序依赖。误区是把 par_unseq 当作普通 par；其中不能依赖锁、I/O、共享可变状态或线程局部执行顺序。
