---
qid: cpp-real-nk-013
type: single
kp: [cpp-memory-mgmt, cpp-concurrency]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: B
tags: [interview-real, nowcoder]
---

关于 `std::shared_ptr` 的线程安全性，下列描述正确的是：

A. `shared_ptr` 是完全线程安全的，所有操作都可以无锁并发
B. **引用计数的更新是线程安全（原子操作）**，但**被管理对象本身不是线程安全的**，多个线程同时使用 `*sp` 修改需要外部同步
C. `shared_ptr` 是完全线程不安全的，所有操作都需要外部锁
D. 引用计数不是原子操作，但 C++14 起标准要求所有共享指针实现必须加锁保护计数字段

---

**解析：**

C++ 标准对 `shared_ptr` 的线程安全保证：

1. **控制块（引用计数）是线程安全的**：拷贝、赋值、析构时的增减引用计数使用 `atomic` 操作，不会出现 use-after-free
2. **同一个 shared_ptr 对象的读写不是安全的**：两个线程同时操作同一个 shared_ptr 对象（一个写空，一个读）会数据竞争；这是两个线程**共享 shared_ptr 对象本身**的问题
3. **被管理对象不是线程安全的**：多个线程通过 shared_ptr 访问底层对象，需要互斥锁保护

常见陷阱：在函数返回 shared_ptr 时用引用传递会导致数据竞争，应该按值传递（值传递安全）。

**来源：** 卡码笔记 C++ 智能指针面试题 / C++ 标准委员会 LWG Issue 2771