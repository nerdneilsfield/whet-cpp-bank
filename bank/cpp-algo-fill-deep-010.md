---
qid: cpp-algo-fill-deep-010
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::reduce", "reduce", "std::transform_reduce", "transform_reduce"]
---

要对 `std::vector<double>` 并行求和（接受 `std::execution::par`），且避免 `std::accumulate` 严格左折叠带来的不可并行性，应改用算法 _______。

---

**解析：**

`std::reduce(policy, first, last, init, binary_op = plus<>{})`（C++17，`<numeric>`）允许任意求值顺序，可加并行策略：

```cpp
auto sum = std::reduce(std::execution::par, v.begin(), v.end(), 0.0);
```

要求 `binary_op` 满足**结合律**（典型实现还假定交换律）。对浮点加法严格意义上**不满足结合律**（舍入误差），所以并行 reduce 结果**不可复现**——这是性能换稳定性的取舍。

需要"并行加 + 元素变换"用 `std::transform_reduce`：

```cpp
auto sqsum = std::transform_reduce(
    std::execution::par,
    v.begin(), v.end(), 0.0, std::plus<>{},
    [](double x){ return x*x; });
```
