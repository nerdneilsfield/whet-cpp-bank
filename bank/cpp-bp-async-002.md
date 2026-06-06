---
qid: cpp-bp-async-002
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

下面"懒计算"代码的最大陷阱是？

```cpp
std::future<int> compute_later() {
    return std::async([] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return expensive_calculation();
    });
    // 默认 launch policy
}

int main() {
    auto fut = compute_later();   // 返回 future

    do_other_work();              // 期望并发执行

    int result = fut.get();       // 拿到结果
}
```

A. future 在 main 中泄漏
B. 默认 launch policy 是 `async | deferred`，编译器可能选 deferred，导致 lambda 在 `fut.get()` 时才在调用线程执行，毫无并发
C. expensive_calculation 不可重入
D. lambda 必须 mutable

---

**解析：**

`std::async(f)` 不指定 launch policy 时，默认为 `std::launch::async | std::launch::deferred`。这是一个 "**实现可任选**" 的模糊语义：

- 如果实现选 `async`：函数在新线程上立刻执行，`do_other_work()` 真正并行
- 如果实现选 `deferred`：函数被推迟，直到 `fut.get()` 或 `fut.wait()` 时**才在调用线程同步执行**——和直接调用 `expensive_calculation()` 没区别！

更糟糕的是：
- `fut.wait_for(0s)` 检查时，对 deferred future **永远返回 `deferred` 状态**，无法用"轮询"判断完成
- 调用方完全没法预测 deferred 还是 async

**实际行为**：GCC libstdc++ 倾向 async，MSVC 在高线程压力下倾向 deferred。这是**跨平台 bug 的常见来源**。

正确做法——**永远显式指定 launch policy**：

```cpp
std::future<int> compute_later() {
    return std::async(std::launch::async, [] {       // 明确 async
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return expensive_calculation();
    });
}
```

更严肃的工程建议：避免使用 `std::async`，用线程池 + `packaged_task` 替代：

```cpp
ThreadPool pool;
std::future<int> compute_later() {
    return pool.enqueue([]{
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return expensive_calculation();
    });
}
```

Scott Meyers 在 Effective Modern C++ 第 36 条专门讨论了这个陷阱：**"Specify std::launch::async if asynchronicity is essential"**.