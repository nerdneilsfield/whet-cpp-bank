---
qid: cpp-algo-fill-deep-010
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::reduce", "reduce", "std::transform_reduce", "transform_reduce"]
---

要对 `std::vector<double>` 并行求和（接受 `std::execution::par`），且避免 `std::accumulate` 严格左折叠带来的不可并行性，应改用算法 _______。

## 解析

答案是 std::reduce，若还需要先映射元素则用 std::transform_reduce。reduce 支持执行策略并允许重排求值顺序，所以可并行。误区是继续用 accumulate；accumulate 是严格左折叠，不能表达并行归约契约。
