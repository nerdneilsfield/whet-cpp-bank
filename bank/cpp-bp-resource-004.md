---
qid: cpp-bp-resource-004
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: A
---

"Rule of Zero" 指什么？下列哪个类**正确遵守了**该规则？

```cpp
// A
class Config {
    std::string name_;
    std::vector<int> values_;
    std::unique_ptr<Validator> validator_;
public:
    Config(std::string n) : name_(std::move(n)) {}
    // 无显式声明的 ctor/dtor/copy/move
};

// B
class Config {
    char* name_;
public:
    Config(const char* n) : name_(strdup(n)) {}
    ~Config() { free(name_); }
};

// C
class Config {
    std::string name_;
public:
    Config(std::string n) : name_(std::move(n)) {}
    Config(const Config& o) : name_(o.name_) {}
    Config& operator=(const Config& o) { name_ = o.name_; return *this; }
    ~Config() {}
};

// D
class Config {
    std::string name_;
public:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = default;
};
```

A. A：使用 RAII 成员，无需任何显式 special member function
B. B：手动管理裸资源
C. C：显式定义所有 special member function
D. D：显式 = default 五大成员

---

## 解析

**Rule of Zero**（Sutter 提出）：**如果你的类的所有成员都是 RAII 的（如 string、vector、unique_ptr），就不要写任何 destructor / copy / move ctor / copy / move assignment**。让编译器自动生成的版本"该 copy 就 copy，该 move 就 move"，这是最简单也最安全的设计。

- **A 正确**：所有成员都是 RAII 的，编译器为该类自动生成正确的 ~ctor、copy、move、assignment。注意 `unique_ptr` 不可拷贝，所以编译器自动让 Config 也不可拷贝（move-only），这正是期望的语义。
- B：用 `char*` 裸指针手动管理，**违反规则**。必须实现 rule of 5 才安全（这里仅写了 dtor，会导致默认 copy 触发 double-free）。
- C：显式定义了 copy 但**没有 move**，触发 rule of 5 陷阱：声明任何 special member 都会**抑制 move 自动生成**，导致 `std::move(config)` 退化为 copy，性能损失。
- D：显式 `= default` 也属于"声明了"，同样会抑制 move 自动生成（实测因编译器版本可能差异，但是不推荐的写法）。

正确做法：让 RAII 成员承担所有资源管理，类自身保持"空"。这是现代 C++ 最重要的设计哲学之一。