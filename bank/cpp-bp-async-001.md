---
qid: cpp-bp-async-001
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

下列使用 `std::async` 的代码，可能有什么问题？

```cpp
auto f1 = std::async(std::launch::async, heavy_compute, 1000000);
auto f2 = std::async(std::launch::async, heavy_compute, 2000000);
auto f3 = std::async(std::launch::async, heavy_compute, 3000000);

// 然后等等
auto r1 = f1.get();
auto r2 = f2.get();
auto r3 = f3.get();
```

A. get() 会阻塞主线程
B. heavy_compute 不可复制
C. 短期内可能创建大量线程（系统线程数目限制），超出后 `std::async` 抛 `std::system_error` 或退化为 deferred
D. std::async 的返回值必须配合 try-catch

---

**解析：**

`std::launch::async` 的语义是：**在** **新线程** **上执行函数**。每个 async 调用创建一个系统线程系统线程的创建数目受操作系统限制（典型 Linux 上 ulimit -u 约为 32000，但实际精力有限——1000 个线程同时运行就已经有上下文切换开销了）。

如果这里 `std::launch::async` 创建了 3 个线程，一般来说没问题。但如果在**循环中调用百次**，或者在其他已经有很多线程的系统里，就可能耗尽资源或触发线程创建失败。

但本题考察一个更隐蔽的行为：`std::async` 如果不指定 `std::launch::async` 且 不指定 launch policy 时，默认是 `std::launch::async | std::launch::deferred`，**实现可以选择 deferred**（懒执行，直到 `.get()` 时才同步执行）。

这里显式指定了 `std::launch::async`，所以 OK。但注意：
- 如果 `std::async` 因资源原因无法创建线程，会抛 `std::system_error`
- Ubuntu/POSIX 默认线程栈 8MB，300 个线程 = 2.4GB 虚存

**更严重的问题是**：这种模式没有限制线程池大小。拷贝 3 次还好，但是如果：
```cpp
std::vector<std::future<int>> futures;
for (auto& item : huge_list)
    futures.push_back(std::async(std::launch::async, process, item));
```
这就是**线程池陷阱**——生产代码应当用 `ThreadPool` 调度到有限数量的线程上，而非无限制创建线程。

正确做法：
```cpp
ThreadPool pool(4);   // 固定 4 线程
auto r1 = pool.enqueue(heavy_compute, 1000000);
auto r2 = pool.enqueue(heavy_compute, 2000000);
auto r3 = pool.enqueue(heavy_compute, 3000000);
auto r1 = r1.get(); auto r2 = r2.get(); auto r3 = r3.get();
```
或使用 OpenMP / Intel TBB 等调度框架。