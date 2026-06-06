---
qid: cpp-mem-med-009
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: B
---

下列 RAII 包装文件描述符的实现中，哪一个最符合 C++ 的资源管理惯例？

```cpp
// 方式 A
class Fd {
    int fd_;
public:
    Fd(int fd) : fd_(fd) {}
    ~Fd() { close(fd_); }
};

// 方式 B
class Fd {
    int fd_ = -1;
public:
    explicit Fd(int fd) : fd_(fd) {}
    ~Fd() { if (fd_ >= 0) ::close(fd_); }

    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;

    Fd(Fd&& o) noexcept : fd_(o.fd_) { o.fd_ = -1; }
    Fd& operator=(Fd&& o) noexcept {
        if (this != &o) { if (fd_ >= 0) ::close(fd_); fd_ = o.fd_; o.fd_ = -1; }
        return *this;
    }
    int get() const { return fd_; }
};
```

A. 方式 A 已经足够，析构里调用 `close` 就是 RAII
B. 方式 B 正确：禁用拷贝、定义移动并把源对象置为"空"状态，避免 double-close
C. RAII 不适合管理 fd 这种非内存资源，应该用 `try/finally` 等价物
D. 应该在拷贝构造里 `dup(fd)`，复制描述符

---

**解析：**

RAII 的核心是"资源的所有权与对象生命周期绑定"，但只写析构函数远远不够。方式 A 的问题：

1. 默认的拷贝构造/赋值会复制 `fd_`，两个 `Fd` 对象持有同一个描述符，析构时会 **double-close**——而 close 后的 fd 可能被内核重新分配给新打开的文件，第二次 close 关掉的可能是别人的 fd，是严重的资源泄漏类 bug。
2. 没有处理"已经被 move 走"的空状态。

方式 B 遵循"rule of five"：禁用拷贝（描述符是独占资源），实现移动，并用哨兵值 `-1` 表示空状态，析构时只关闭有效 fd。这与 `std::unique_ptr` 的设计思想完全一致。

D 的 `dup` 方案改变了语义（变成共享而不是独占），不是惯例做法，且增加成本和复杂度。C 错误——RAII 适用于任何"获取-释放"配对的资源（fd、锁、句柄、GL 资源等），并不局限于内存。

## Explanation

正确答案是 B，文件描述符是独占资源，RAII 包装类必须在析构中关闭，并禁止拷贝以避免多个对象 double-close 同一个 fd。移动构造/移动赋值应转移 fd 并把源对象置为无效值（如 -1），保证源对象析构时不会再关闭。方式 A 只有析构没有拷贝控制，默认拷贝会造成严重资源所有权错误。
