---
qid: cpp-taste-class-002
type: single
kp: [cpp-classes, cpp-move-semantics, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, ownership]
---
一个 Logger 类持有 `std::unique_ptr<FileSink>`，需要允许被放入容器（必须可移动）。哪个设计品味最好？

```cpp
// A
class Logger {
    std::unique_ptr<FileSink> sink_;
public:
    Logger(std::unique_ptr<FileSink> s) : sink_(std::move(s)) {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = default;
    Logger& operator=(Logger&&) = default;
};

// B
class Logger {
    std::unique_ptr<FileSink> sink_;
public:
    Logger(std::unique_ptr<FileSink> s) : sink_(std::move(s)) {}
    Logger(Logger&& o) noexcept : sink_(std::move(o.sink_)) {}
    Logger& operator=(Logger&& o) noexcept { sink_ = std::move(o.sink_); return *this; }
};

// C
class Logger {
    std::unique_ptr<FileSink> sink_;
public:
    explicit Logger(FileSink s) : sink_(std::make_unique<FileSink>(std::move(s))) {}
    Logger(Logger&& o) noexcept : sink_(std::move(o.sink_)) {}
    Logger& operator=(Logger&& o) noexcept { sink_ = std::move(o.sink_); return *this; }
};

// D
class Logger {
    std::unique_ptr<FileSink> sink_;
public:
    Logger(std::unique_ptr<FileSink> s) : sink_(std::move(s)) {}
};
```

A. A — 明确 delete 拷贝、default 移动，意图最清晰
B. B — 手写移动更可控，避免隐藏的 bug
C. C — 按值接 FileSink，调用方不用显式构造 unique_ptr，使用体验更好
D. D — 编译器隐式生成的已经正确，没必要写多余的

---

**解析：**

选 D。Rule of Five 的"三/五/零"在这里结合成**隐式移动 + 显式删除拷贝**——但也不需要，因为 unique_ptr 已经帮你做了。

逐一品味：

- **A**：`default` 移动操作在移动构造中含 `noexcept`、移动赋值含 `noexcept`，但又重复写了 `delete` 拷贝——这**暴露了对默认行为的认知**：`unique_ptr` 成员本身不可拷贝，所以类的拷贝操作会被隐式 `delete`，写 `= delete` 是冗余的。多余的 `= delete` 本身无害，但说明作者没完全信任默认规则。
- **B**：手写了编译器已经能做好的事。`unique_ptr` 的移动操作是 noexcept 且正确的，`= default` 移动完全够用。手写等同于在说"我知道编译器会生成什么"——但既然一样，为什么不 `= default`？多了几句代码让 review 者多花时间检查而已。
- **C**：最坏的选择。`Logger(std::unique_ptr<FileSink>)` 改成 `explicit Logger(FileSink s)`——现在调用方必须交出 FileSink 的所有权但不知道内部发生了 `make_unique`。更糟的是：如果 FileSink 是多态基类，这个接口**切断了多态性**，因为只能传值。
- **D**：只写了一个自定义构造函数，其余全部让编译器生成。`unique_ptr` 不是可拷贝的 → 拷贝操作自动 `= delete`。`unique_ptr` 可移动且 noexcept → 移动操作自动 `= default` and noexcept。析构自动调用 `unique_ptr` 的析构→ 正确。**四行代码表达了完整的所有权语义：独占、可移动、不可拷贝、自动释放。**

**核心识别点**：
- `unique_ptr` 成员 = 隐式 `delete` 拷贝 + 隐式 noexcept 移动 + 正确析构
- 看到多余的手写移动/delete 拷贝（和编译器行为一致时）→ 警觉，是不是在重复劳动
- 构造函数里的 `unique_ptr` 参数 = 告诉调用方"交所有权"
- 值参数接之后 `make_unique` 的方案→ 破坏多态性

**来源：** 手写题。C++ Core Guidelines C.63: "Move-only types should have `=default` move operations"。