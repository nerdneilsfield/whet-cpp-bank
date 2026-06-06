---
qid: cpp-algo-fill-deep-008
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::execution::par_unseq", "par_unseq", "execution::par_unseq"]
---

C++17 在 `<execution>` 中提供 4 个执行策略：`seq`、`par`、`unseq`（C++20）、________。其中既允许多线程并行又允许同一线程内矢量化交错执行的策略是 ________（请填策略名，可带或不带命名空间限定）。

---

**解析：**

C++17 三策略 + C++20 第 4 个：

| 策略 | 多线程 | 矢量化/交错 | 谓词约束 |
|---|---|---|---|
| `seq` (sequenced_policy) | ✗ | ✗ | 无 |
| `par` (parallel_policy) | ✓ | ✗ | 无数据竞争 |
| `unseq` (unsequenced_policy, C++20) | ✗ | ✓ | 不可同步原语 |
| **`par_unseq` (parallel_unsequenced_policy)** | ✓ | ✓ | 无数据竞争 + 不可同步原语 |

`par_unseq` 限制最严：lambda 内不能用 mutex、`std::atomic`（某些操作）、动态内存分配、I/O——任何会阻塞或带状态的操作，因为同一线程内可能"暂停 A 切到 B"。

异常从并行算法谓词中逃逸 → `std::terminate`。
