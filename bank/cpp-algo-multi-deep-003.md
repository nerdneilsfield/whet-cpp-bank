---
qid: cpp-algo-multi-deep-003
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: [A, C, D]
---

关于 C++17 并行算法（`std::execution::par`），下列哪些**正确**？（多选）

```cpp
std::for_each(std::execution::par, v.begin(), v.end(), [&](int& x){ ... });
```

A. 用户提供的可调用对象**不得引发数据竞争**，否则 UB
B. 标准要求实现必须使用 OS 线程（如 pthread）
C. 可调用对象抛出未捕获的异常会导致 `std::terminate` 被调用
D. `par_unseq` 还要求可调用对象内部不可调用同步原语（mutex、I/O 等）

## Explanation

正确选项是 A、C、D。并行算法不会替用户同步，共享状态造成数据竞争就是未定义行为。标准不规定必须用 OS 线程；而并行策略下用户函数异常逃逸会调用 terminate，par_unseq 还要求函数体适合向量化，不能使用同步原语或 I/O。
