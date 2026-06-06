---
qid: cpp-real-tencent-009
type: single
kp: [cpp-concurrency, cpp-types]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: B
tags: [interview-real, tencent]
---
```cpp
volatile bool flag = false;

// 线程 1
void producer() {
    /* 准备数据 */
    flag = true;
}

// 线程 2
void consumer() {
    while (!flag) {}    // 等待
    /* 消费数据 */
}
```
关于 `volatile` 关键字，以下说法**正确**的是：

A. volatile 保证 flag 的读写在多线程下是原子的，可代替 atomic 使用
B. volatile 仅告诉编译器"不要把这个变量缓存到寄存器、不要优化读写"，但不保证原子性、不建立 memory barrier，因此上述代码在多核 CPU 下可能因 reordering 而失败
C. volatile 等价于 atomic，性能完全相同
D. volatile 主要用于 Java 多线程，C++ 中没什么用

---

**解析：**

选 B。volatile 是 C++ 中**最被误用的关键字**之一。

**volatile 真正的含义：**
- 告诉编译器：每次访问这个变量都必须真实读写内存（不要缓存到寄存器）
- 适用场景：内存映射 I/O 寄存器、信号处理函数中的变量、setjmp/longjmp 间共享的变量

**volatile 不保证的：**
- **不保证原子性**：`volatile int x; x++` 仍然是非原子的（先读、改、写三步）
- **不建立 memory barrier**：CPU 可以重排 volatile 读写和其他内存操作的顺序
- **不保证可见性**：在多核 CPU 上，缓存一致性问题仍存在

**正确的多线程同步**应该用：
```cpp
std::atomic<bool> flag{false};

// 线程 1
flag.store(true, std::memory_order_release);

// 线程 2
while (!flag.load(std::memory_order_acquire)) {}
```
`atomic<T>` 提供：
1. 原子操作（不可分割）
2. memory ordering（防止 reordering）
3. 缓存一致性保证

**结论：** Java 的 volatile 和 C++ 的 volatile 完全不同。Java volatile 包含 happens-before 语义（类似 C++ atomic）；C++ volatile 没有这些保证。**C++ 多线程绝不要用 volatile 做同步。**

**来源：** 腾讯后端 C++ 面试（参考：cppreference volatile、Herb Sutter "Volatile vs Volatile"）

## Explanation

正确答案是 B。
选 B。volatile 是 C++ 中最被误用的关键字之一。
