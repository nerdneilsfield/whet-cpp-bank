---
qid: cpp-bp-resource-001
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: B
---

下面手写 socket RAII 封装的最大隐患是什么？

```cpp
class Socket {
    int fd_;
public:
    explicit Socket(int fd) : fd_(fd) {}
    ~Socket() { if (fd_ >= 0) ::close(fd_); }

    Socket(const Socket& other) : fd_(::dup(other.fd_)) {}
    Socket& operator=(const Socket& other) {
        if (this != &other) {
            ::close(fd_);
            fd_ = ::dup(other.fd_);
        }
        return *this;
    }
};
```

A. 未提供 move 构造，性能差
B. 未禁用拷贝（或不提供 move），导致默认 move 由拷贝合成时仍 dup，并且 close 异常情况下可能 double-close
C. dup 比 close 慢，应该用 fcntl
D. close 应该用 shutdown 替代

---

## 解析

文件描述符（fd）是**唯一所有权**资源。拷贝 fd 应该慎重，因为：
1. dup 出新 fd 是新增内核资源（fd 表是有限的），可能耗尽
2. 大多数场景下用户**不希望** copy（如线程间传递、放入容器）
3. 一旦提供了 copy，C++ 规则会**抑制 move 的隐式生成**（rule of 5），导致 `std::vector<Socket>` 的扩容用拷贝，性能跌倒拷贝水平

最严重的是第 3 点：用户写 `vec.push_back(std::move(sock))`，期望 move，但实际触发 dup。这是难以发现的性能 bug。

更好的设计：fd 是 unique resource，应当**只支持 move 不支持 copy**（unique_ptr 语义）。

正确做法：
```cpp
class Socket {
    int fd_ = -1;
public:
    explicit Socket(int fd) : fd_(fd) {}
    ~Socket() { if (fd_ >= 0) ::close(fd_); }

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&& o) noexcept : fd_(std::exchange(o.fd_, -1)) {}
    Socket& operator=(Socket&& o) noexcept {
        if (this != &o) {
            if (fd_ >= 0) ::close(fd_);
            fd_ = std::exchange(o.fd_, -1);
        }
        return *this;
    }
};
```