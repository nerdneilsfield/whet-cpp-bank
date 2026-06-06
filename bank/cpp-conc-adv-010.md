---
qid: cpp-conc-adv-010
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

关于 `std::future::get()` 的阻塞行为，正确的是？

A. `get()` 立即返回，如果值未就绪则返回默认值
B. `get()` 会阻塞当前线程，直到关联的 `promise` 调用 `set_value()` 或 `set_exception()`
C. `get()` 只能调用一次；第二次调用返回缓存值
D. `get()` 有超时机制，默认等待 1 秒后抛出异常

## 解析

正确答案是 B。`std::promise` 负责设置结果，关联的 `std::future` 负责等待并取得结果。选项 B 的表述“｀get()｀ 会阻塞当前线程，直到关联的 ｀promise｀ 调用 ｀set_value()｀ 或 ｀set_exception()｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
