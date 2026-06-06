---
qid: cpp-taste-class-001
type: single
kp: [cpp-classes, cpp-special-members, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, rule-of-zero]
---
一个类持有 `std::vector<std::string>` 成员，需要提供拷贝语义。四个版本哪个品味最好？

```cpp
// A
class Tags {
    std::vector<std::string> tags_;
public:
    Tags() = default;
    Tags(const Tags& o) : tags_(o.tags_) {}
    Tags(Tags&& o) noexcept : tags_(std::move(o.tags_)) {}
    Tags& operator=(const Tags& o) { tags_ = o.tags_; return *this; }
    Tags& operator=(Tags&& o) noexcept { tags_ = std::move(o.tags_); return *this; }
    ~Tags() = default;
};

// B
class Tags {
    std::vector<std::string> tags_;
public:
    Tags() = default;
    Tags(const Tags& o) { tags_ = o.tags_; }
    Tags(Tags&& o) { tags_ = std::move(o.tags_); }
    Tags& operator=(const Tags& o) { if (this != &o) tags_ = o.tags_; return *this; }
    Tags& operator=(Tags&& o) { if (this != &o) tags_ = std::move(o.tags_); return *this; }
    ~Tags() = default;
};

// C
class Tags {
    std::vector<std::string> tags_;
public:
    Tags() = default;
};

// D
class Tags {
    std::vector<std::string> tags_;
public:
    Tags() = default;
    Tags(const Tags& o) : tags_(o.tags_) {}
    Tags(Tags&& o) noexcept : tags_(std::move(o.tags_)) {}
    Tags& operator=(Tags o) noexcept { swap(o); return *this; }
    void swap(Tags& o) noexcept { tags_.swap(o.tags_); }
    ~Tags() = default;
};
```

A. A — 明确把五个特殊成员全写了，不会有任何隐式生成的意外
B. B — 加了自赋值保护，比 A 更安全
C. C — 一句额外代码都不用写，最干净
D. D — copy-and-swap 用法最地道，异常安全最好

---

**解析：**

选 C。Rule of Zero 在这里是唯一正确的选择。

逐一品味：

- **A**：五句手写全是 `vector` 默认实现的**精确翻版**。`vector` 的拷贝构造、移动构造、拷贝赋值、移动赋值、析构全部正确实现——那为什么要再写一遍？每多写一行代码就多一个审查负担。而且 A 把赋值返回值写成了非引用（排版妥协还是笔误？），这反而是 bug。
- **B**：加了 `if (this != &o)` 自赋值检查——但 `vector::operator=` 本身已**正确支持自赋值**（先拷贝再释放是标准做法，虽然没保证。实际上 libstdc++/libc++ 都安全）。手写自赋值保护是 Rule of Three 时代的遗产，在现代 C++ 中告诉读者"我对标准库没信心"。
- **C**：什么都不写。`vector<string>` 自带正确的五成员。增加 `swappable` 特质？已有 `std::swap` 特化。需要 noexcept？`vector` 的移动操作已正确标注。需要异常安全？`vector::operator=` 提供强保证。**很多时候最地道的 C++ 就是什么都不写。**
- **D**：copy-and-swap 本身是好用法，但**在不必要的时候过度设计了**。D 引入了一个额外 `swap` 函数（虽然由 vector 提供），让拷贝赋值变成了通过拷贝构造 + move 的间接路线，编译器优化不掉的情况下多了一次 move。对一个已经正确且不需要自定义语义的类，加 copy-and-swap 是在**解决一个不存在的问题**。

**核心识别点**：
- Rule of Zero 的适用条件：所有成员都是 RAII 类型 → 什么都不写
- 手写自赋值检查 `this != &other` 在现代 C++ 中几乎总是冗余的
- copy-and-swap 解决核心问题是"异常安全 + 统一代码路径"，不是"替 Rule of Zero 代劳"
- 看见 `= default` 一行和看见五句 `= default` 一样好——前者更好

**来源：** 手写题。Rule of Zero 见 C++ Core Guidelines C.20；自赋值讨论见 StackOverflow "Is the self-assignment check necessary?"。