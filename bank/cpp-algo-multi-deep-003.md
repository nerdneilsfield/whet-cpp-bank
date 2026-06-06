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

---

**解析：**

- A ✅：并行规范不提供同步，谓词必须无数据竞争。
- B ❌：标准只描述行为，可基于线程池、纤程、GPU offload 等任意实现。GCC 的 par 实现基于 TBB。
- C ✅：从并行算法用户代码逃逸的异常调用 `std::terminate`（[algorithms.parallel.exceptions]）。
- D ✅：`par_unseq` 允许矢量化交错执行，谓词需 "vectorization-safe"，禁止同步操作。

实际效果：选 par 还是 par_unseq 取决于谓词是否完全 lock-free。无策略版（串行）异常正常传播。
