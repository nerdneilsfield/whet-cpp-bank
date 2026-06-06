---
qid: cpp-bp-async-003
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

下面 `wait_for` 的轮询代码有什么 bug？

```cpp
auto fut = std::async(std::launch::async, []{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
});

while (true) {
    auto status = fut.wait_for(std::chrono::milliseconds(100));
    if (status == std::future_status::ready) {
        std::cout << "result = " << fut.get();
        break;
    }
    // 处理其他事情
    do_some_work();
}
```

A. 应该用 `wait` 而非 `wait_for`
B. `wait_for` 还有 `deferred` 状态，对 deferred future 永远返回 `deferred`，循环无法退出
C. fut.get() 在循环结束后再调
D. 100ms 间隔太长

---

## 解析

`std::future::wait_for` 返回的 `std::future_status` 有 3 种值：
- `ready`：结果就绪
- `timeout`：超时还未就绪
- `deferred`：future 关联的是 deferred 任务，**永远不会自动执行**

代码只检查 `ready`，其他都继续 `do_some_work()`。如果这个 future 恰好是 deferred 的：
- `wait_for` 立刻返回 `deferred`（不消耗时间也不执行任务）
- 循环条件为真继续轮询
- 任务从不执行，结果永远不 ready
- → **死循环**

虽然本例显式用了 `std::launch::async`，但更通用的代码（如来自外部 API 的 future）可能是 deferred 的。正确写法必须处理三种状态：

```cpp
while (true) {
    auto status = fut.wait_for(std::chrono::milliseconds(100));
    if (status == std::future_status::deferred) {
        // 强制求值（或换思路）
        fut.wait();   // 同步执行
        break;
    }
    if (status == std::future_status::ready) {
        std::cout << "result = " << fut.get();
        break;
    }
    // timeout，继续做其他事
    do_some_work();
}
```

或者更简洁地，配合 Scott Meyers 的"防呆"模式：先检查 deferred 一次，确认是 async：

```cpp
if (fut.wait_for(0s) == std::future_status::deferred) {
    // 是 deferred，直接 get
    auto r = fut.get();
} else {
    // 是 async，轮询
    while (fut.wait_for(100ms) != std::future_status::ready) {
        do_some_work();
    }
    auto r = fut.get();
}
```

工程教训：**`wait_for` 返回值必须三分支处理**，否则就是 hidden bug。