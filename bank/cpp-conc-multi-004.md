---
qid: cpp-conc-multi-004
type: multi
kp: [cpp-concurrency]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::future` / `std::promise`，**哪些说法是正确的**？（多选）

A. `promise::set_value` 调用后，与之关联的 `future::get` 可取到结果。
B. 同一个 `promise` 只能 `set_value` 一次，重复设置会抛 `future_error`。
C. `std::async(std::launch::deferred, f)` 返回的 future，其 `get` 不会阻塞，立即返回。
D. `std::shared_future` 允许多个线程并发等待与读取同一结果。

---

**解析：**

A 正确：典型的 promise/future 一次性同步机制。
B 正确：重复 `set_value` / `set_exception` 抛 `promise_already_satisfied`。
C 错误：`launch::deferred` 表示延迟执行，`get` 时同步运行任务，可能阻塞。
D 正确：`shared_future` 支持多线程多次 `get` 同一结果。

## Explanation

正确答案是 A、B、D。`std::promise` 负责设置结果，关联的 `std::future` 负责等待并取得结果。 A 正确：｀promise::set_value｀ 调用后，与之关联的 ｀future::get｀ 可取到结果。；B 正确：同一个 ｀promise｀ 只能 ｀set_value｀ 一次，重复设置会抛 ｀future_error｀。；C 错误：｀std::async(std::launch::deferred, f)｀ 返回的 future，其 ｀get｀ 不会阻塞，立即返回。；D 正确：｀std::shared_future｀ 允许多个线程并发等待与读取同一结果。。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
