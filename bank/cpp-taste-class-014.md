---
qid: cpp-taste-class-014
type: single
kp: [cpp-classes, cpp-cpp11, cpp-move-semantics]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, callback]
---
一个 `Button` 类需要存放一个"按下时调用的回调"。回调可能是 lambda、函数指针、bind 等。哪个设计品味最好？

```cpp
// A
class Button {
    void (*on_click_)();
public:
    void set_handler(void (*fn)()) { on_click_ = fn; }
    void click() { if (on_click_) on_click_(); }
};

// B
class Button {
    std::function<void()> on_click_;
public:
    void set_handler(std::function<void()> fn) { on_click_ = std::move(fn); }
    void click() { if (on_click_) on_click_(); }
};

// C
template<typename Handler>
class Button {
    Handler on_click_;
public:
    explicit Button(Handler h) : on_click_(std::move(h)) {}
    void click() { on_click_(); }
};

// D
class Button {
    std::vector<std::function<void()>> handlers_;
public:
    void add_handler(std::function<void()> fn) { handlers_.push_back(std::move(fn)); }
    void click() { for (auto& h : handlers_) h(); }
};
```

A. A — 函数指针最轻量，无堆分配、无类型擦除开销
B. B — `std::function` 兼容所有 callable，可在运行时替换
C. C — 模板参数让 Handler 在编译期确定，零开销
D. D — 支持多个 handler，更灵活

---

**解析：**

选 B。这道题考的是**接口需求与抽象工具的对齐**。

逐一品味：

- **A**：函数指针 `void(*)()` **无法捕获 lambda 的捕获列表**。如果调用方写 `btn.set_handler([&counter](){ ++counter; })`，函数指针就接不住——只能接无捕获 lambda。GUI 回调几乎总要捕获 this/state，函数指针在现代代码中表达回调是 C 思维残留。性能上确实最小（一个指针），但接口能力严重受限。
- **B**：`std::function<void()>` 接受所有可调用对象——lambda（有/无捕获）、bind、成员函数指针 + 对象、函数指针、自定义 `operator()` 类。**这是回调接口的现代标准**。代价：可能有小型对象优化（SBO）外的堆分配、虚调用 + 类型擦除的微小开销。但对 GUI Button 这种低频事件，可忽略。`std::move(fn)` 让传入的 function 不被多次拷贝。
- **C**：模板 Button 让 Handler 在编译期确定 → 零开销。**但破坏性问题**：Button 现在是模板，**不同 Handler 的 Button 是不同类型**。`vector<Button<???>>` 无法存放——一组按钮怎么管理？这只适合**单一组件、单一回调**的场景，不适合"按钮"这种通用 UI 部件。
- **D**：支持多 handler 是合理需求**对某些场景**——但 Button "按下" 通常是单一动作（导航、提交）。如果真要多观察者，那应该是 EventBus / Signal 而不是 Button 的固有特性。这里强行加 vector 是过度设计。

`std::function` 的代价（小堆分配 + 间接调用）在 99% 的 GUI/事件场景下完全可接受，换来的是接口的通用性、运行时可替换性、和 lambda 的无缝集成。

**为什么不是 C？** 模板是好工具但代价是**类型扩散**：每个不同的 lambda 生成不同的 Button 类型，无法异质化存储。如果你的需求是"建立一个 Button 池/列表"，模板就不通。这是模板和类型擦除的核心权衡。

**核心识别点**：
- 函数指针 → 不能接捕获 lambda，C 时代回调方案
- `std::function` → 接受所有 callable，运行时替换，类型擦除
- 模板回调 → 零开销但类型扩散，无法同质容器
- 多回调需求 → 通常是 Observer/Signal 模式，不是组件内 vector

**来源：** 手写题。`std::function` 的设计哲学；Sean Parent "Inheritance Is The Base Class of Evil" 中关于 callable 类型擦除的讨论。