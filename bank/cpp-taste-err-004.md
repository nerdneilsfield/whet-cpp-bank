---
qid: cpp-taste-err-004
type: single
kp: [cpp-classes, cpp-exceptions]
primary_kp: cpp-classes
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
要写一个 `Connection` 类，构造时尝试连接远程服务，连接失败要让调用方知道。四个版本功能相同，哪个品味最好？

```cpp
// A
class Conn_a {
    Socket sock_;
public:
    explicit Conn_a(std::string_view host) : sock_(connect(host)) {
        if (!sock_.valid()) throw std::runtime_error("connect failed");
    }
};

// B
class Conn_b {
    Socket sock_;
    bool bad_ = false;
public:
    explicit Conn_b(std::string_view host) {
        sock_ = connect(host);
        if (!sock_.valid()) bad_ = true;
    }
    bool good() const { return !bad_; }
};

// C
class Conn_c {
    Socket sock_;
    bool initialized_ = false;
public:
    Conn_c() = default;
    bool init(std::string_view host) {
        sock_ = connect(host);
        initialized_ = sock_.valid();
        return initialized_;
    }
};

// D
class Conn_d {
    Socket sock_;
    Conn_d(Socket s) : sock_(std::move(s)) {}
public:
    static std::optional<Conn_d> make(std::string_view host) {
        Socket s = connect(host);
        if (!s.valid()) return std::nullopt;
        return Conn_d(std::move(s));
    }
};
```

A. A — 构造函数失败就抛异常，对象要么构造成功要么不存在
B. B — 设置 bad_ flag，让调用方调用 good() 检查，类似 ifstream 的设计
C. C — 两阶段构造（默认 ctor + init()），失败时返回 false
D. D — 私有 ctor + 工厂函数返回 optional，避免异常

---

**解析：**

选 A。这道题考 **"C++ 对象构造的二元论：构造成功 = 对象存在 = 不变式成立"**。

C++ 对象的核心约定是：**ctor 成功返回 ⇒ 对象不变式成立**。任何"对象存在但内部状态可能不对"的设计都破坏这条约定——读者每次访问对象都要先检查 `if (good())`，每个成员函数都要写 `if (!initialized_) return error`，类的复杂度立刻翻倍。

A 通过抛异常恪守这条约定：构造失败 = 异常抛出 = **对象根本没存在过**（栈对象不会进入作用域，堆对象 `new` 抛了 = 内存自动归还）。后续任何使用 `Conn` 的代码都不需要"先检查再用"，所有成员函数都假定连接有效。

逐一品味：

- **B**：`ifstream` 风格的"半成品对象"——确实是标准库的历史选择，**但这是 C++98 异常机制不成熟时代的妥协，不是好榜样**。它强迫所有用户：(1) 构造后 `if (!c.good()) ...` 检查，忘了就是 bug；(2) 每个 member function 内部还得防御 bad 状态。流类如果今天重新设计，大概率会用异常或 optional。
- **C**：两阶段构造 = "对象先无效存在、然后 init"——**最差的一种**。`Conn c; c.init(host);` 有四种状态：未调 init、调 init 失败、调 init 成功、调 init 多次。每个成员函数都要处理至少前两种，类型成了状态机。再加上"忘了调 init 就用 = UB"——比 B 更糟。这是 COM / DirectX 风格，在原生 C++ 里没有充分理由。
- **D**：工厂 + `optional<Conn>` 是一种合法选择——**避免异常、把失败编码到返回类型里**。但它有两个代价：(1) 类不能简单地作为成员/基类（`Member m{host};` 写不了，必须 `std::optional<Member> m_ = Member::make(host);`，再各种 `if (m_)`）；(2) 没有错误原因（连不上是 DNS 失败？端口拒？超时？）。如果场景里"连接失败"是常见且需要静默处理的，D 是合理的；如果是"应当连上、连不上是异常情况"，A 更直接。**A 是默认选择，D 是不允许异常时的备选**。

**核心识别点：**

- ctor 成功 = 不变式成立 → 失败就抛
- 看见 `bool good()` / `bool bad()` → 警觉半成品对象
- 看见两阶段构造（default ctor + init） → 警觉状态机化
- 真不允许异常（嵌入式、不能 unwind 的边界）→ 工厂 + `optional`/`expected`
- 看见 ctor 里"失败也不报告" → 类型说谎，最差

A 的另一处品味在 `: sock_(connect(host))` 用 member initializer 而非 ctor body 赋值——这让 `sock_` 一次到位构造，而不是先默认构造再赋值。B 和 C 都先默认构造 `sock_` 再覆盖，**反映出对"对象生命周期从 member-init list 就开始"的不熟悉**。

**来源：** 手写题。"Constructor failure = throw" 见 Bjarne Stroustrup *The C++ Programming Language* 4e §17.4；C++ FAQ "How can I handle a constructor that fails?"；C++ Core Guidelines C.40, C.41, C.42；流类的两阶段设计批评见 Herb Sutter "GotW #66: Constructor Failures"。

## Explanation

正确答案是 A。这道题考 "C++ 对象构造的二元论：构造成功 = 对象存在 = 不变式成立"。
这道题考 "C++ 对象构造的二元论：构造成功 = 对象存在 = 不变式成立"。
逐一品味： B：`ifstream` 风格的"半成品对象"——确实是标准库的历史选择，但这是 C++98 异常机制不成熟时代的妥协，不是好榜样。
