---
qid: cpp-real-tencent-010
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: A
tags: [interview-real, tencent]
---
```cpp
// 场景 A: 临界区耗时 10 微秒（很短）
std::mutex   m1;        // 互斥锁
std::atomic_flag spin = ATOMIC_FLAG_INIT;  // 自旋锁

// 场景 B: 临界区耗时 100 毫秒（较长，含 I/O）
```
关于互斥锁（mutex）和自旋锁（spinlock）的选择，以下说法**正确**的是：

A. 短临界区（如 < 几百纳秒）适合自旋锁：避免线程睡眠/唤醒的开销（上下文切换通常需要几微秒）；长临界区适合互斥锁：避免 CPU 空转浪费
B. 自旋锁总是比互斥锁快，应优先使用
C. 互斥锁不需要内核切换，是用户态实现
D. 在单核 CPU 上自旋锁优于互斥锁

---

**解析：**

选 A。互斥锁与自旋锁的选择取决于**临界区长度**和**CPU 上下文切换成本**。

**互斥锁（mutex）：**
- 获取失败时：线程被**睡眠**，挂起到等待队列
- 释放时：唤醒等待队列中的线程（涉及 syscall：futex / WaitForSingleObject）
- 开销：上下文切换约 1-10 微秒
- 适合：临界区较长（> 几微秒）、线程数多于 CPU 核数

**自旋锁（spinlock）：**
- 获取失败时：在循环中**忙等待**（"spin"），不睡眠
- 优势：避免上下文切换的开销
- 劣势：占用 CPU；如果临界区长，会浪费大量 CPU
- 适合：临界区极短（< 1 微秒）、多核 CPU、持锁线程不会被抢占

**为什么单核 CPU 上自旋锁很糟糕？**
持锁线程要释放锁，必须运行；自旋线程占着 CPU → 持锁线程无法运行 → 死锁式空转，直到时间片用完被抢占。所以**单核上自旋锁劣于互斥锁**。

**实际 std::mutex 在很多实现中是混合的（adaptive mutex）**：先自旋一小段时间，失败再睡眠，兼顾两者优点。

C 错，互斥锁在快速路径可以是用户态（如 Linux futex 在无竞争时不进内核），有竞争时需要 syscall。D 错，单核下自旋锁很差。

**来源：** 腾讯后端 C++ 面试（参考：Linux 内核源码、《Linux 多线程服务端编程》）