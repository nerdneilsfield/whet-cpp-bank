---
qid: cpp-conc-multi-hard-005
type: multi
kp: [cpp-concurrency]
difficulty: hard
answer_key: [A, B, D]
---
关于 `std::thread` 的生命周期与终止语义，以下说法正确的是哪些？

```cpp
void worker();
{
    std::thread t(worker);
    // 离开作用域时 t 还 joinable 会发生什么？
}
```

A. 若 `std::thread` 析构时仍 `joinable()`（既未 `join` 也未 `detach`），会调用 `std::terminate` 直接终止整个程序。
B. `detach()` 让线程脱离 thread 对象独立运行，但若 detach 的线程访问了已销毁的栈变量或主程序退出时仍在运行，是未定义行为。
C. `std::thread` 的拷贝构造与拷贝赋值均合法，可让多个 thread 对象共同管理同一底层线程。
D. C++ 标准未提供"取消（cancellation）"机制，要协作式终止线程需用 `std::atomic<bool> stop_flag` 或 C++20 的 `std::jthread + stop_token`。

---

**解析：**

A 正确：标准明确规定，joinable 的 `std::thread` 在析构时调用 `std::terminate`，强制程序员显式做出 join 或 detach 决定，避免静默泄露线程。
B 正确：detach 后线程独立运行，无法再 join，访问已死栈对象或进程退出未结束都是 UB。常见 detach 滥用导致难调试的崩溃。
C 错误：`std::thread` 是 move-only 的——拷贝构造与拷贝赋值都被 delete，避免两个对象同时管理同一线程。可以 move 转移所有权但不能拷贝。
D 正确：POSIX 有 `pthread_cancel`，但 C++ 标准刻意没有强制取消机制（因 unwind 安全性极难保证）；推荐协作式 stop flag，C++20 的 `jthread` 内置了 `stop_token` 接口并在析构时自动 request_stop+join。