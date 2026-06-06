---
qid: cpp-taste-class-005
type: single
kp: [cpp-classes, cpp-memory-mgmt, cpp-special-members]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, encapsulation]
---
一个类内部持有一段可变长缓冲区，需要对外提供数据访问。哪个设计品味最好？

```cpp
// A
class Buffer {
    std::vector<char> buf_;
public:
    char* data() { return buf_.data(); }
    const char* data() const { return buf_.data(); }
    std::size_t size() const { return buf_.size(); }
};

// B
class Buffer {
    std::vector<char> buf_;
public:
    std::string_view view() const { return {buf_.data(), buf_.size()}; }
    void append(const char* s, std::size_t n) { buf_.insert(buf_.end(), s, s + n); }
};

// C
class Buffer {
    std::vector<char> buf_;
public:
    std::span<const char> read() const { return {buf_.data(), buf_.size()}; }
    void write(std::span<const char> data) {
        buf_.insert(buf_.end(), data.begin(), data.end());
    }
};

// D
class Buffer {
    std::vector<char> buf_;
public:
    const std::vector<char>& vec() const { return buf_; }
    std::vector<char>& vec() { return buf_; }
};
```

A. A — 暴露 raw ptr 但给出 `size()`，调用方可随意读写，最灵活
B. B — `string_view` 只读、`append` 写，读写分离，implicit conversion 方便
C. C — `span` 提供范围视角，读写都通过 span，类型安全且不引入 string 语义
D. D — 直接暴露 vector 引用，调用方可以完全控制 buffer，最透明

---

**解析：**

选 C。这题考的是**暴露多少内部实现是最优雅的折中**。

逐一品味：

- **A**：暴露 `char* data()` 意味着任何调用方都可以 `buffer.data()[3] = 'x'`、越界访问、传入 C 函数等。虽然灵活，但把内部 `vector` 的地址暴露出去，如果以后改成 `deque<char>` 或 mmap 文件，data() 返回的指针不再有效——**实现泄漏**。
- **B**：`string_view` 是**语义误导**——buffer 存的是二进制数据（char），不是字符串。`string_view` 的打印、查找、比较等接口对二进制数据（含 '\0'）的行为是混乱的。用类型来表达语义：二进制数据该用 `span<const char>`，而非 `string_view`。而且只提供了 `append` 没有提供 `overwrite`、`resize` 等——接口太受限。
- **C**：`std::span<const char>` 准确地表达了"**一块连续内存的只读视图**"——不假设是字符串、不提供字符串操作、不涉及所有权。接受参数也用 `span<const char>`，让调用方可以从 vector/array/C数组 传入数据。对称性好。缺点是 C++20 才标准可用（C++17 可用 gsl::span）。但品味上这是最正确的抽象。
- **D**：直接返回 `const vector<char>&` 和 `vector<char>&`——**完全暴露了实现**。今天用 `vector<char>` 明天改 `deque<char>` 或 `std::string`，所有调用方都需修改。而且返回可变引用意味着调用方可以 push_back、resize、clear——完全破坏了 Buffer 类的封装控制。这个接口等于"我说我是 Buffer，实际上我是 vector——你知道吗？"

C 的 `span` 方案是"provide abstraction, not implementation"的典范。对比 A 的 raw ptr、B 的 `string_view` 错配、D 的裸露 vector，C 在**类型安全、语义准确、实现隐藏**之间取得了最佳平衡。

**核心识别点**：
- 暴露 raw ptr → 实现泄漏 + 越界风险
- 二进制数据用 `span` 而非 `string_view`（后者隐含字符串语义）
- 返回内部容器引用 → 完全破坏封装
- `span` 作为参数类型 → 适配多种来源（vector、array、C数组），是最通用的范围抽象

**来源：** 手写题。C++ Core Guidelines I.4: "Make interfaces precisely and strongly typed"；GSL 指南使用 span 作为数组参数标准。

## Explanation

正确答案是 C。但品味上这是最正确的抽象。
C：`std::span<const char>` 准确地表达了"一块连续内存的只读视图"——不假设是字符串、不提供字符串操作、不涉及所有权。
B：`string_view` 是语义误导——buffer 存的是二进制数据（char），不是字符串。
