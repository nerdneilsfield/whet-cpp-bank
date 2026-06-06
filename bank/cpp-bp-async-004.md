---
qid: cpp-bp-async-004
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

`std::packaged_task` 和 `std::promise` 在 C++ 中都可以从异步任务传结果到 future。下列哪个场景**必须**用 `promise`？

```cpp
// 场景 1：一个耗时的计算，结果由新线程返回
int heavy(int x) { return x * x; }

// 场景 2：回调式 API——注册一个 C 风格回调，回调中传递结果
void register_callback(void (*cb)(int, void*), void* ctx);

// 场景 3：执行函数 f，返回 future
template<class F>
auto wrap(F f) -> std::future<decltype(f())> { ... }
```

A. 场景 1
B. 场景 3
C. 场景 2：回调式 API 的回调函数在不确定的时间和上下文被调用，需要 promise 显式传递结果
D. 两者等价

---

## 解析

`packaged_task` 和 `promise` 都是 "producer" 侧，区别在于：

| | `packaged_task` | `promise` |
|---|---|---|
| 绑定到 | 一个**可执行体**（callable） | 无绑定 |
| 调用时 | 执行 callable，自动填充 future | 用户手动 `set_value` / `set_exception` |
| 典型场景 | "我有一份工作，包起来丢给谁执行" | "我收到数据了，手写传递出去（回调/事件）" |

- 场景 1 `heavy(x)`：函数有返回值，适合 `packaged_task`（或直接 `std::async`）
- 场景 3 `wrap(f)`：同样适合 `packaged_task`
- **场景 2**：回调函数被 C 库在任意线程、任意时刻调用，返回值是空的（void），调用者无法控制。需要 `promise` 来让回调函数内手动设置值

```cpp
// 场景 2 的典型解法
std::future<int> do_async_work() {
    auto prom = std::make_shared<std::promise<int>>();
    auto fut = prom->get_future();

    register_callback([](int result, void* ctx) {
        // 回调内手动设置
        static_cast<std::promise<int>*>(ctx)->set_value(result);
    }, prom.get());   // 注意生命周期管理！

    return fut;
}
```

用 `promise` 当回调接收器是 C++ 异步可组合性扩展到 C 生态的关键桥梁。

另外注意 `packaged_task` 本身不创建线程，它只是"包装"，需要显式在线程或线程池中调用：
```cpp
std::packaged_task<int(int)> task(heavy);
auto fut = task.get_future();
std::thread(std::move(task), 42).detach();  // 必须手动启动
int result = fut.get();
```