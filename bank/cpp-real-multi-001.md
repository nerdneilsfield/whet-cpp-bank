---
qid: cpp-real-multi-001
type: multi
kp: [cpp-memory-mgmt, cpp-concurrency]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: [A, C]
tags: [interview-real, multi-vendor]
---
```cpp
std::shared_ptr<Widget> g_ptr = std::make_shared<Widget>();

// Thread 1
void t1() {
    auto local = g_ptr;     // 拷贝 shared_ptr
    local->use();
}

// Thread 2
void t2() {
    g_ptr.reset();          // 重置全局 shared_ptr
}
```
关于 `std::shared_ptr` 的线程安全性，以下说法**正确**的是（多选）：

A. 引用计数本身是原子操作，因此**多线程同时拷贝**指向同一对象的不同 shared_ptr 实例是安全的
B. 多线程同时读写**同一个 shared_ptr 实例**（如上述 g_ptr）是安全的，因为引用计数是原子的
C. shared_ptr **所指向的对象** 本身的并发访问需要用户加锁；shared_ptr 不会提供对象级别的同步
D. 在 C++20 之前，对同一 shared_ptr 实例的并发读写需要使用 `std::atomic_load`/`std::atomic_store` 系列；C++20 引入了 `std::atomic<std::shared_ptr<T>>`
E. shared_ptr 的所有操作都是无锁的（lock-free）

---

**解析：**

正确答案：**A、C、D**。

**A 正确：**  控制块的引用计数是 atomic，**不同 shared_ptr 实例**（即使指向同一对象）的拷贝/销毁是线程安全的。

**B 错误：** 同一个 shared_ptr 实例（如 g_ptr）的并发读写**不安全**！shared_ptr 内部有两个指针（对象指针 + 控制块指针），同时修改这两个指针不是原子的。Thread 1 拷贝时可能读到 Thread 2 reset 中间状态，导致 UB。

**C 正确：** shared_ptr 只保证控制块的引用计数线程安全，对**对象内容**的访问需用户用 mutex 等保护。

**D 正确：** C++11/14/17 时代用 `std::atomic_load(&sp)`、`std::atomic_store(&sp, new_sp)` 这套自由函数版本（C++20 弃用）。C++20 引入 `std::atomic<std::shared_ptr<T>>` 模板特化，更现代。

**E 错误：** shared_ptr 的操作不一定 lock-free。`std::atomic<shared_ptr>` 是否 lock-free 取决于实现，通常**不是** lock-free（用 mutex 保护内部状态）。

**实际工程建议：**
- 全局 shared_ptr 频繁更新 → 用 `atomic<shared_ptr<T>>` 或 mutex 保护
- 多线程读 + 少量写 → 考虑 RCU / hazard pointer

**来源：** 跨厂高频混淆点（参考：cppreference shared_ptr、Herb Sutter《Atomic Smart Pointers》）