---
qid: cpp-real-nk-034
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: B
tags: [interview-real, bytedance]
---

```cpp
auto f = std::async([] { return slow_compute(); });  // (A)
auto f = std::async(std::launch::async, [] { ... }); // (B)
auto f = std::async(std::launch::deferred, [] { ... }); // (C)
```

下列说法**正确**的是：

A. (A) (B) (C) 都立即在新线程中执行任务
B. **(A) 是默认 policy `async | deferred`，由实现决定是新线程还是 deferred；(C) 不会创建新线程，直到 `f.get()` 才在调用线程中同步执行**
C. (C) 一定在 future 析构时执行
D. 三者性能完全等价

---

**解析：**

`std::async` 的三种 launch policy：

1. **`std::launch::async`**：立即在**新线程**中异步执行
2. **`std::launch::deferred`**：**懒求值**，任务不立即执行，直到 `f.get()` 或 `f.wait()` 才在调用线程中同步执行（"延迟函数"）
3. **默认（不指定）**：实际等价于 `async | deferred`，**由实现决定**，可能根本不创建新线程

最大陷阱：默认 policy 的 future 析构时——
- 如果是 async 启动的：析构会**阻塞**（join）直到任务完成
- 如果是 deferred 的：析构时根本没执行过

实际产线代码强烈建议：
- 显式指定 `std::launch::async`（如果要异步）
- 或者用 `std::thread` 替代

`std::launch::deferred` 的 future 不调用 get 永远不执行，没"自动析构时执行"的语义。

**来源：** 字节并发面试题 / Effective Modern C++ Item 35-36