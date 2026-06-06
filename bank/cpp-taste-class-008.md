---
qid: cpp-taste-class-008
type: single
kp: [cpp-classes, cpp-memory-mgmt, cpp-special-members]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, pimpl]
---
用 Pimpl 模式隐藏 `Widget` 的实现。四个头文件声明哪个品味最好？（Impl 在 .cpp 中完整定义）

```cpp
// A
class Widget {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    Widget();
    ~Widget();
    Widget(Widget&&) noexcept = default;
    Widget& operator=(Widget&&) noexcept = default;
};

// B
class Widget {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    Widget();
    ~Widget();
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;
};

// C
class Widget {
    struct Impl;
    Impl* pimpl_;
public:
    Widget();
    ~Widget();
    Widget(Widget&& o) noexcept;
    Widget& operator=(Widget&& o) noexcept;
};

// D
class Widget {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    Widget();
};
```

A. A — unique_ptr + 移动 =default，最简洁现代的 Pimpl
B. B — 头文件只声明，cpp 里统一 =default，遵守 "complete-type 才生成" 的规则
C. C — raw ptr 避免 unique_ptr 的类型完整性问题
D. D — 让编译器隐式生成全部特殊成员函数

---

**解析：**

选 B。Pimpl 的核心陷阱是：**`unique_ptr<Impl>` 要求特殊成员函数的定义点处 `Impl` 是完整类型**。

逐一品味：

- **A**：**编译错误**，最常见的 Pimpl 新手坑。在头文件中写 `Widget(Widget&&) noexcept = default;` 是要求编译器**在头文件这个点定义**移动构造。但移动构造可能需要析构 `pimpl_`（赋值时），而 `unique_ptr<Impl>` 的析构调用了 `delete pimpl_`，需要 `Impl` 完整定义。此处 Impl 仅前置声明，触发 static_assert 失败或将操作隐式 `= delete`。
- **B**：正确做法。头文件中仅**声明**（declare）移动操作和析构，不在头文件中提供定义。在 `.cpp` 中 `struct Widget::Impl { ... };` 完整定义之后，用 `Widget::~Widget() = default;`、`Widget::Widget(Widget&&) noexcept = default;` 等生成定义。此时 `unique_ptr<Impl>` 看到完整 Impl，正确生成。Herb Sutter 推荐做法。
- **C**：`Impl* pimpl_` 是**古老但能工作**的方案。raw ptr 没有编译期类型完整性约束。但需要手动 `delete pimpl_`，**违背 RAII**：构造函数中途抛异常就泄漏。移动操作也需手写指针交换。能编译，但是 C++98 风格。
- **D**：让编译器隐式生成全部——但 `~Widget()` 隐式定义在调用点（可能是头文件包含处的其它 cpp），而那里 `Impl` 不完整 → `unique_ptr` 的析构 static_assert 失败 → 编译错误。和 A 一样的陷阱，但更隐蔽（错误信息会在调用方代码中爆出）。

**核心识别点**：
- `unique_ptr<Incomplete>` 需要特殊成员函数的**定义点**处类型完整
- `= default` 在头文件中等同于"在此定义"，对前向声明类型会失败
- Pimpl 的正确模式：头文件只声明，cpp include 完整类型后 `= default`
- 看到 `unique_ptr<Pimpl前置声明>` + 头文件里 `= default` → 编译陷阱

**来源：** 手写题。C++ Core Guidelines C.149；Herb Sutter "GotW #100: Compilation Firewalls"。