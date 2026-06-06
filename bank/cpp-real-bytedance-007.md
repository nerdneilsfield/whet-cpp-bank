---
qid: cpp-real-bytedance-007
type: single
kp: [cpp-concurrency]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: C
tags: [interview-real, bytedance]
---
```cpp
// 方案 A: 使用 atomic
std::atomic<int> counter{0};
void inc() { counter.fetch_add(1, std::memory_order_relaxed); }

// 方案 B: 使用 mutex 保护 int
int counter = 0;
std::mutex m;
void inc() {
    std::lock_guard<std::mutex> lk(m);
    ++counter;
}
```
关于 `std::atomic` 和 `std::mutex` 的选择，以下说法**最准确**的是：

A. atomic 总是比 mutex 快，能用 atomic 就用 atomic
B. atomic 只适合 bool 类型，其他类型必须用 mutex
C. atomic 适合保护**单一变量的简单操作**（如计数、标志位、单指针交换）；mutex 适合保护**多个变量组成的复合状态**或**长临界区**。atomic 在无锁算法中关键，但实现复杂正确性难
D. atomic 是 C++17 引入的，C++11 只有 mutex

---

**解析：**

选 C。两者的本质不同：

**std::atomic：**
- 提供**单个变量**的原子操作（load/store/exchange/fetch_add 等）
- 对于一些类型（bool、int、指针），在主流硬件上由 CPU 指令直接支持（LOCK 前缀、CAS）
- 没有"锁竞争"概念，多线程同时操作只是序列化执行
- 内存序（memory_order）允许精细控制：relaxed / acquire / release / seq_cst
- **缺点：** 不能保护"复合操作"。如 `if (counter < 10) counter++;` 不是原子的（read-check-write 三步），需要 CAS 循环或锁

**std::mutex：**
- 保护任意大小的临界区
- 失败时进入睡眠 → 上下文切换开销
- 编程模型简单，正确性容易保证
- 适合需要原子性的**多步操作**

**典型选择：**
| 场景 | 选择 |
|------|------|
| 计数器（只递增） | atomic.fetch_add |
| 标志位（一次写多次读） | atomic<bool> |
| 单指针交换（lock-free 链表头） | atomic<T*>.compare_exchange |
| HashMap、复杂数据结构 | mutex |
| 多个相关变量同步更新 | mutex |
| 长时间持锁（含 I/O） | mutex |

A 错，atomic 在无竞争时快，高竞争时可能比 mutex 更慢（CPU 缓存行 ping-pong）。B 错，atomic 支持所有 trivially copyable 类型（大对象可能用锁实现，is_lock_free 检查）。D 错，atomic 是 C++11 引入。

**来源：** 字节 C++ 后端面试（参考：cppreference、《C++ Concurrency in Action》）