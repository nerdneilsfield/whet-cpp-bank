---
qid: cpp-taste-conc-007
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: D
tags: [code-taste, best-practice]
---
worker 线程算出一个结果（int），主线程要拿到。四个版本功能相同，哪个品味最好？

```cpp
// A
std::queue<int> q;
std::mutex mu;
std::condition_variable cv;
void worker_a() {
    int r = compute();
    { std::lock_guard lk(mu); q.push(r); }
    cv.notify_one();
}
int main_a() {
    std::thread t(worker_a);
    std::unique_lock lk(mu);
    cv.wait(lk, []{ return !q.empty(); });
    int r = q.front(); q.pop();
    t.join();
    return r;
}

// B
int result_b;
std::atomic<bool> ready_b{false};
void worker_b() {
    result_b = compute();
    ready_b.store(true, std::memory_order_release);
}
int main_b() {
    std::thread t(worker_b);
    while (!ready_b.load(std::memory_order_acquire)) {}
    t.join();
    return result_b;
}

// C
int result_c;
std::mutex mu_c;
void worker_c() {
    int r = compute();
    std::lock_guard lk(mu_c);
    result_c = r;
}
int main_c() {
    std::thread t(worker_c);
    t.join();
    std::lock_guard lk(mu_c);
    return result_c;
}

// D
int main_d() {
    auto fut = std::async(std::launch::async, compute);
    return fut.get();
}
```

A. A — 用 `queue + cv` 是教科书写法，最显并发功底
B. B — 用 `atomic<bool> flag + memory_order` 最低延迟
C. C — `join()` 后再读是天然 happens-before，配 mutex 双保险
D. D — `std::async` + `future::get`，让标准库处理所有同步

---

**解析：**

选 D。这道题考 **"想做什么 → 用最贴合意图的工具"**——传递"一个值"用 `future`，而不是搭一套队列/标志/锁。

D 一行启动、一行获取，**异常也自动通过 future 传播**（`compute()` 抛了什么、`fut.get()` 就抛什么）。"传递一个一次性的值"在 C++11 之后就有了专门的工具叫 `std::future`，再去搭 queue / atomic flag / 共享变量都是绕远路。

逐一品味：

- **A**：用 thread-safe queue 来传**一次性的一个值**——`queue` 的语义是"流式多元素 + FIFO"，这里完全用不上。代码量 5 行的同步逻辑做一件 1 行的事。在生产者-消费者多元素场景里 A 是正确写法，**但在"传一个值"这件事上是大材小用、词不达意**。
- **B**：`atomic flag + 忙等` 是上一题已经批评过的 anti-pattern——CPU 100% 自旋等结果，还要自己处理 memory order（虽然 release/acquire 写对了，但 95% 的工程师写不对）。**手写 acquire/release 应该是最后手段**，标准库里早就有 future 把这事做对了。
- **C**：看起来用 `join()` 做同步很聪明——`thread::join()` 确实建立 happens-before 关系，读 `result_c` 不会有数据竞争。但 (1) 那个 mutex 完全多余（join 已经同步过了）；(2) `result_c` 是文件级全局变量，**没法多次并发调 main_c**；(3) 万一 `compute()` 抛异常，worker 线程会调 `std::terminate`——而 D 会把异常优雅地传到 main。**少了异常通道**是这种"全局变量 + join"方案的隐藏致命缺点。
- **D**：贴合意图、自动处理异常、无全局状态、可重入、可组合（`.wait_for` / `then` / 多 future 并发）。

**核心识别点：**

- 后台算一个值返回 → `std::async + future`
- 后台流式产生多个值 → `queue + cv` 或 `concurrent_queue`
- 看见 `atomic<bool> ready + busy wait` → 警觉自旋 + 想想 future
- 看见 worker 函数写全局变量再 join → 警觉异常通道丢失
- "做这件事 C++11 之前怎么做" vs "C++11 之后怎么做" → 后者通常 1-2 行解决

A 是"我会写并发"的人写的；B 是"我懂 memory model"的人写的；C 是"我知道 join 同步"的人写的；D 是"我先问该用什么工具"的人写的。**code-taste 里，先问 idiom 永远赢过秀技术**。

**来源：** 手写题。`std::async` 替代手工同步见 Herb Sutter "Use async if the result is needed in this thread"；异常通过 future 传播见 ISO/IEC 14882:2017 §33.10 [futures]；Anthony Williams *C++ Concurrency in Action* 2e §4.2 系统对比了 future / promise / packaged_task / async。
