---
qid: cpp-taste-conc-004
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
要在后台跑一个耗时计算，返回结果给主线程。四个版本功能相同，哪个品味最好？

```cpp
int heavy_compute(int x);

// A
std::future<int> run_a(int x) {
    return std::async(std::launch::async, heavy_compute, x);
}

// B
std::future<int> run_b(int x) {
    std::promise<int> p;
    auto fut = p.get_future();
    std::thread([p = std::move(p), x]() mutable {
        try { p.set_value(heavy_compute(x)); }
        catch (...) { p.set_exception(std::current_exception()); }
    }).detach();
    return fut;
}

// C
std::future<int> run_c(int x) {
    std::packaged_task<int(int)> task(heavy_compute);
    auto fut = task.get_future();
    std::thread t(std::move(task), x);
    t.detach();
    return fut;
}

// D
std::future<int> run_d(int x) {
    return std::async(heavy_compute, x);
}
```

A. A — `std::async(std::launch::async, ...)` 显式指定异步策略，最简洁也最明确
B. B — 手写 `promise + thread` 最显基本功，能控制每一处细节
C. C — `packaged_task` 是中间方案，封装好任务又能自己挑线程，最灵活
D. D — `std::async(heavy_compute, x)` 让运行时自己决定要不要新开线程，最自动

---

**解析：**

选 A。这道题考 **"用 `std::async` 时一定要显式传 `std::launch::async`"** 这条细节品味。

A 一行代码、明确表达"我要在后台异步执行"。返回 `std::future<int>`，调用方 `.get()` 时拿结果或拿到原始异常。异常通过 future 自然传播，不需要手写任何 catch 塞回去。

逐一品味为什么其他版本不好：

- **B**：把 `std::async` 内部做的事全部展开手写——`promise`、捕获异常塞进去、`thread` 启动、`detach`。**写对了，但全是已经被标准库做好的胶水代码**。而且 `detach` 也是隐患（见下一题），调用方拿到 future 没问题，但底层线程对象就脱缰了。
- **C**：`packaged_task` 的真正用途是**把任务先打包、之后再投到某个执行器/线程池里跑**——比如自己实现一个 thread pool 时，pool 的 worker thread 从队列里取 `packaged_task` 执行。这里只是想"现在跑一下"，根本没有"任务和执行解耦"的需求，用 `packaged_task` 是套了一层多余的间接层。
- **D**：**这是 `std::async` 的著名陷阱**。不带 launch policy 时，标准规定的默认是 `std::launch::async | std::launch::deferred`——意味着实现可以选择**deferred**，即"在调用方 `.get()` 时才在调用方线程同步执行"，根本没起到异步效果。Scott Meyers 在 *Effective Modern C++* Item 36 专门写过这条："Specify `std::launch::async` if asynchronicity is essential"。看似无害的省略，可能让"后台计算"变成"主线程阻塞"。

**核心识别点：**

- 用 `std::async` → **必须**带 `std::launch::async`，不能省
- 看见 `std::async(f, args...)`（无 policy） → 警觉 deferred 陷阱
- 手写 `promise + thread` 模拟 `std::async` → 警觉，是不是该直接用 `std::async`
- `packaged_task` → 只在"任务先入队、后执行"的 executor 场景用
- 异步函数的异常 → 通过 future 自然传播，不要手写 try/catch 塞 promise

A 比 D 多打 21 个字符（`std::launch::async, `），换来的是对"异步还是同步"的确定性承诺——这是品味题里典型的"细节决定味道"案例。

**来源：** 手写题。`std::async` launch policy 陷阱见 Scott Meyers *Effective Modern C++* Item 36；`packaged_task` 与 `async` 区分见 Anthony Williams *C++ Concurrency in Action* 2e §4.2.1-4.2.3。
