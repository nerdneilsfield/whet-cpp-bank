---
qid: cpp-perf-obj-002
type: single
kp: [cpp-move-semantics, cpp-special-members]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要往 `std::vector<MyString>` 里 push_back 多个元素，让 vector 重新分配时**走 move 而不是 copy**。下面四个 MyString 实现功能等价，哪个最值得采用？

```cpp
// A
class MyString {
    char* p_; std::size_t n_;
public:
    MyString(MyString&& o) : p_(o.p_), n_(o.n_) { o.p_=nullptr; o.n_=0; }
    MyString(const MyString& o) { /* deep copy */ }
    ~MyString() { delete[] p_; }
    // ... assignment, ctor from const char* ...
};

// B
class MyString {
    char* p_; std::size_t n_;
public:
    MyString(MyString&& o) noexcept : p_(o.p_), n_(o.n_) { o.p_=nullptr; o.n_=0; }
    MyString(const MyString& o) { /* deep copy */ }
    ~MyString() { delete[] p_; }
    // ... assignment, ctor from const char* ...
};

// C
class MyString {
    char* p_; std::size_t n_;
public:
    MyString(MyString&& o) throw() : p_(o.p_), n_(o.n_) { o.p_=nullptr; o.n_=0; }
    MyString(const MyString& o) { /* deep copy */ }
    ~MyString() { delete[] p_; }
    // ... assignment, ctor from const char* ...
};

// D
class MyString {
    char* p_; std::size_t n_;
public:
    MyString(MyString&& o) : p_(o.p_), n_(o.n_) { o.p_=nullptr; o.n_=0; }
    MyString(const MyString& o) noexcept { /* deep copy */ }
    ~MyString() { delete[] p_; }
    // ... assignment, ctor from const char* ...
};
```

A. A — move ctor 像普通函数，正常实现就行
B. B — move ctor 加 noexcept，明示不会抛
C. C — move ctor 加 throw()，C++03 的空异常规约
D. D — copy ctor 加 noexcept，强保证拷贝不会抛

---

**解析：**

选 B。这道题考的是"`std::vector` 在 reallocation 时如何选择 move vs copy 的关键依据"。

逐一品味：

- **A**：`std::vector` 在重新分配时调用 `std::move_if_noexcept(elem)`——这个工具的规则是：如果 move ctor 是 noexcept 或者 copy ctor 不存在，返回 rvalue 走 move；否则返回 const lvalue 走 copy。**A 的 move 没标 noexcept**，所以 vector reallocation 时**不敢 move，会走 copy**——每个元素都要 deep copy 全部字符串内容。100 万 string 每个 100 字节就是 100 MB 的额外 memcpy + 同等的 free/alloc。**比 B 慢一个数量级**。
- **B**：move ctor 标了 `noexcept`，`move_if_noexcept` 返回 rvalue，vector reallocation 走 move——只需交换三个指针/字段。整个 reallocation 几乎免费（除了新内存分配本身）。**正确做法**。这是 C++11 引入 `move_if_noexcept` 时刻意设计的"强异常安全 vs 性能"权衡机制：vector 在中途异常时无法回滚已 move 的元素，所以只有保证不抛才敢用 move。
- **C**：`throw()` 是 C++03 的空异常规约，C++17 起 deprecated、C++20 移除。**在现行标准里行为：在 GCC 上等同 noexcept、在某些场景仍会装额外的"调用 unexpected"机制**。可以工作，但已淘汰且语义不一。不该用。
- **D**：把 noexcept 标到 copy ctor 上是误解——`move_if_noexcept` 检查的是 **move ctor** 的 noexcept 性，不看 copy ctor。D 的 vector reallocation 还是走 copy。这是"似是而非"的陷阱选项。

如果 MyString 像 std::string 一样所有成员都是简单类型，move ctor **可以也应当**是 noexcept。**省略它的代价是 vector 性能下降一个数量级**——这是 noexcept 在 C++11 后最实际的性能影响场景。

**核心识别点：**
- 看见自定义类的 move ctor 缺 noexcept → 警觉 vector reallocation 会退回 copy
- 看见 `throw()` → 警觉是过时语法，改 noexcept
- `std::move_if_noexcept` 是 vector 在性能 vs 异常安全之间的实际仲裁器
- noexcept 不只是文档：它直接影响 STL 算法的代码路径选择
- 简单类型的 move（指针+size 字段交换）几乎不可能抛——把 noexcept 标上去是免费的性能

**来源：** Scott Meyers, "Effective Modern C++", Item 14 "Declare functions noexcept if they won't emit exceptions"；C++11 标准 [vector.modifiers]、[utility]；Howard Hinnant, "noexcept and move constructors" blog post.

## Explanation

选 B，因为 `std::vector` 扩容时会优先使用 `noexcept` 的移动构造来维持异常安全。移动构造未标 `noexcept` 时，vector 可能退回深拷贝，导致重分配成本暴涨。误区是给拷贝构造标 `noexcept` 或使用过时的 `throw()`，这不是现代容器选择移动的正确信号。
