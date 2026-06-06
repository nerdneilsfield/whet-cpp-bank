---
qid: cpp-mem-hard-002
type: single
kp: [cpp-memory-mgmt]
difficulty: hard
answer_key: C
---

多线程环境下，关于 `std::shared_ptr<T>::use_count()` 的语义，下列说法正确的是？

```cpp
std::shared_ptr<int> sp = std::make_shared<int>(42);
// 线程 A：拷贝/析构 sp
// 线程 B：读 sp.use_count()
```

A. `use_count()` 返回精确值，可用于判断"是否仅剩当前线程持有"
B. `use_count()` 内部使用互斥锁，调用代价等同 `std::mutex::lock`
C. `use_count()` 仅返回一个**近似**值，多线程下不能用来做生命周期决策
D. `use_count()` 是 `constexpr` 的，编译期即可求值

## 解析

标准对 `shared_ptr::use_count` 的描述为"返回当前 `shared_ptr` 共享所有权的对象个数，可能是**近似**值"。引用计数本身是原子的，但读操作只是 `relaxed` 读取，调用结束后值可能立即过时；典型实现里也不会加锁。因此 `use_count()` 仅适合调试/统计，绝不能用作并发决策（例如 "若 == 1 则视为独占"）。要做独占判断需用 `weak_ptr::lock` + 自身设计，或重新设计为单一所有者。B 错误：读取通常无锁；D 错误：它不是 `constexpr`，且涉及运行期原子状态。
