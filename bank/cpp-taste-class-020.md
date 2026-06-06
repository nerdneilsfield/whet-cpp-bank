---
qid: cpp-taste-class-020
type: single
kp: [cpp-classes, cpp-special-members, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, rule-of-zero, default-delete]
---
一个 `Connection` 类持有 socket 句柄（独占资源）。下面四种特殊成员函数声明哪种品味最好？

```cpp
// A
class Connection {
    int fd_ = -1;
public:
    explicit Connection(const std::string& host);
    ~Connection() { if (fd_ != -1) ::close(fd_); }
};

// B
class Connection {
    int fd_ = -1;
public:
    explicit Connection(const std::string& host);
    ~Connection() { if (fd_ != -1) ::close(fd_); }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&& o) noexcept : fd_(std::exchange(o.fd_, -1)) {}
    Connection& operator=(Connection&& o) noexcept {
        if (this != &o) {
            if (fd_ != -1) ::close(fd_);
            fd_ = std::exchange(o.fd_, -1);
        }
        return *this;
    }
};

// C
class Connection {
    int fd_ = -1;
public:
    explicit Connection(const std::string& host);
    ~Connection() = default;
    Connection(const Connection&) = default;
    Connection(Connection&&) = default;
    Connection& operator=(const Connection&) = default;
    Connection& operator=(Connection&&) = default;
};

// D
class Connection {
    int fd_ = -1;
public:
    explicit Connection(const std::string& host);
    ~Connection() { if (fd_ != -1) ::close(fd_); }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};
```

A. A — 只写构造和析构，让编译器隐式生成其他的，最简洁
B. B — Rule of Five 完整：delete 拷贝、实现 move，明确独占语义
C. C — 五个特殊成员全部 = default，让编译器全管
D. D — delete 拷贝就够了，move 不需要支持

---

**解析：**

选 B。这题考**Rule of Three/Five 不适用什么 vs 真的需要 Rule of Five 的场景**。

逐一品味：

- **A**：定义了析构却没声明拷贝/移动——根据 Rule of Five 规则的派生：
  - 用户定义了析构 → **编译器仍隐式生成 copy ctor 和 copy assignment**（C++11 起 deprecated 但仍生成）
  - 用户定义了析构 → **编译器不生成 move ctor 和 move assignment**
  
  结果：拷贝构造**按位拷贝 fd_**——两个 Connection 实例持有同一个 fd_，析构时双重 `::close(fd)`——**double close 的 UB**。同时不能移动 Connection（move 操作被抑制）。**典型的 Rule of Three 违反**。
- **B**：精确的 Rule of Five：
  - delete 拷贝 → 表达 "fd 独占"
  - 实现 move → Connection 可以放入 vector、按值返回、用 swap 等
  - 析构释放 fd
  - 默认构造 fd_ = -1，让 move 走后的对象处于可析构状态
  
  这是手工资源管理的标准 Rule of Five。
- **C**：`= default` 全部 → 拷贝构造按位拷贝 fd_，和 A 一样的 double close 问题。`= default` 不是"安全"，它就是"编译器默认会做的事写出来"。对资源管理类来说这等于退化。
- **D**：禁拷贝**但不支持 move**——Connection 不能放进 `vector<Connection>`、不能按值返回（C++17 前的某些场景）、不能 `std::move` 转移所有权。这让 Connection 成为"被严重限制的类"——用户必须用 `unique_ptr<Connection>` 等包装才能传递。损失了 modern C++ 的常用模式。
  
  D 这种"只禁拷贝"是 C++98 时代的写法。C++11 引入 move 后，独占资源应该是"禁拷贝 + 支持 move"。

Rule of Five 的精髓：**用户定义了五个特殊成员的任何一个，就应该考虑其余四个**。但不是机械地全部写——而是按需选择：
- 拷贝有意义吗？→ 实现 or delete
- 移动有意义吗？→ 实现 or delete or = default
- 析构需要特殊逻辑吗？→ 实现 or = default

对独占资源类（socket、file handle、GPU 资源），典型组合就是 B 的方案。

**核心识别点**：
- 写了自定义析构 → 必须考虑 Rule of Five（编译器规则会让 move 被抑制）
- 独占资源 → delete 拷贝 + 实现 move（不只是 delete 拷贝）
- `= default` 不能拯救按位语义不对的类
- 把构造函数标 explicit，析构里检查空状态，move 后留下"已交出"的空标识

**来源：** 手写题。Scott Meyers "Effective Modern C++" Item 17: "Understand special member function generation"；C++ Core Guidelines C.21。

## Explanation

正确答案是 B。这题考Rule of Three/Five 不适用什么 vs 真的需要 Rule of Five 的场景。
同时不能移动 Connection（move 操作被抑制）。
`= default` 不是"安全"，它就是"编译器默认会做的事写出来"。
