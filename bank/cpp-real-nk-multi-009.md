---
qid: cpp-real-nk-multi-009
type: multi
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: [A, B, D]
tags: [interview-real, alibaba]
---

关于 `std::thread` 和并发 API，下列说法**正确**的有：

A. **`std::thread` 对象在析构时必须被 join 或 detach**，否则调用 `std::terminate` 终止程序
B. **硬件并行核心数可以通过 `std::thread::hardware_concurrency()` 获取**（返回 0 表示无法检测）
C. 多个线程可以同时读写同一个 `std::vector` 而不需要锁，因为 STL 容器是线程安全的
D. **`std::jthread`（C++20）在析构时自动 join**，并可响应 `std::stop_token` 请求协作式停止

---

**解析：**

A 对：C++11 thread 的"要么 join 要么 detach 要么 terminate"规则是 C++ 线程设计的痛点之一。
```cpp
void f() {
    std::thread t(some_func);
    // 如果这里抛异常了，t 析构时没 join/detach → terminate
    t.join();
}
```
B 对：`hardware_concurrency()` 返回硬件支持的并行线程数（通常是核心数），0 表示信息不可用。

C **错**：STL 容器不是线程安全的。多个线程同时写（或一个写同时一个读）`std::vector` 是数据竞争，导致**未定义行为**。但多个线程同时读（无写操作）是安全的。

D 对：C++20 `std::jthread` 解决 A 的问题：
- 析构时自动 `request_stop()` + `join()`
- 内置 `std::stop_token` 机制，取消协作方便
- 替代 `std::thread` 在大部分场景

**来源：** 阿里秋招 C++ 并发面试题 / cppreference thread

## Explanation

正确答案是 [A, B, D]。
A 对：C++11 thread 的"要么 join 要么 detach 要么 terminate"规则是 C++ 线程设计的痛点之一；B 对：hardware_concurrency() 返回硬件支持的并行线程数（通常是核心数），0 表示信息不可用。
C 错：STL 容器不是线程安全的。多个线程同时写（或一个写同时一个读）std::vector 是数据竞争，导致未定义行为。但多个线程同时读（无写操作）是安全的；D 对：C++20 std::jthread 解决 A 的问题： 析构时自动 request_stop() + join() 内置 std::stop_token 机制，取消协作方便 替代 std::thread 在大部分场景。
