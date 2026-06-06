---
qid: cpp-bp-resource-005
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: C
---

下列资源管理代码的问题在哪？

```cpp
class Connection {
    int fd_;
    std::mutex mu_;
public:
    Connection(int fd) : fd_(fd) {}
    ~Connection() {
        std::lock_guard lk(mu_);   // ← 析构函数加锁
        if (fd_ >= 0) {
            send_close_frame(fd_);  // 可能抛
            ::close(fd_);
        }
    }
};
```

A. 析构函数不应使用 lock_guard
B. send_close_frame 抛异常时析构函数会传播异常，可能 terminate
C. 同时存在：析构加锁矛盾（对象正在销毁，其他线程不该再访问）+ 析构抛异常风险
D. 应改用 unique_lock

---

## 解析

这段代码有两个严重问题：

**问题 1：析构函数中加锁的语义矛盾。** 当一个对象正在析构时，**任何其他线程都不应该再持有指向它的引用**——否则 use-after-free 不可避免。如果你需要在析构时加锁来保护，说明你的对象生命周期管理本身就有缺陷（应该用 `shared_ptr` 或外部同步保证唯一所有权后再析构）。

**问题 2：析构函数中可能抛异常。** C++11 起，析构函数默认 `noexcept`。`send_close_frame` 抛出会立刻 `std::terminate`。即使去掉 noexcept，析构函数抛异常在栈展开期间（另一个异常处理中）也会直接 terminate。

正确做法：析构函数应当**简单且不抛异常**。复杂的关闭流程应当显式调用 `close()` 函数让用户主动处理错误，析构作为兜底：

```cpp
class Connection {
    int fd_ = -1;
public:
    Connection(int fd) : fd_(fd) {}
    ~Connection() {
        if (fd_ >= 0) {
            try { send_close_frame(fd_); } catch (...) {}  // 吞掉
            ::close(fd_);
        }
    }
    // 显式接口让用户处理错误
    void shutdown() {
        send_close_frame(fd_);
        ::close(fd_);
        fd_ = -1;
    }
};
```