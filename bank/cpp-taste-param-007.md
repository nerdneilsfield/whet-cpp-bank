---
qid: cpp-taste-param-007
type: single
kp: [cpp-memory-mgmt, cpp-move-semantics]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: B
---

`Registry::add` 想接收一个**所有权要转交给** Registry 的 `Widget`。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
class Registry {
    std::vector<std::unique_ptr<Widget>> items_;
public:
    void add(const std::unique_ptr<Widget>& w) { items_.push_back(std::move(const_cast<std::unique_ptr<Widget>&>(w))); }
};
```

```cpp
// B
class Registry {
    std::vector<std::unique_ptr<Widget>> items_;
public:
    void add(std::unique_ptr<Widget> w) { items_.push_back(std::move(w)); }
};
```

```cpp
// C
class Registry {
    std::vector<std::unique_ptr<Widget>> items_;
public:
    void add(std::unique_ptr<Widget>&& w) { items_.push_back(std::move(w)); }
};
```

```cpp
// D
class Registry {
    std::vector<std::unique_ptr<Widget>> items_;
public:
    void add(Widget* w) { items_.push_back(std::unique_ptr<Widget>(w)); }
};
```

A. A 段：`const&` 配 `const_cast`，避免左值时报错，且能把所有权"骗"出来。
B. B 段：按值接 `unique_ptr`，调用方必须显式 `std::move`，所有权转移意图刻在 API 上。
C. C 段：`&&` 强迫右值，意图最明确，比按值少一次形参移动。
D. D 段：裸指针接 + 函数内 `make` 一个 unique_ptr 接管所有权，最灵活、最兼容旧 API。

## 解析

正确答案是 **B**。

- **A 段（错且危险）**：`const_cast` 掉 `const` 然后 `move`，是直接破坏 const 契约的 UB 温床；调用方传 `const` 变量后底层资源被偷走，再用就是悬空。即使语法过编译，是教科书级反模式。
- **B 段（好）**：按值接 `unique_ptr` 是 sink unique_ptr 的标准范式（Herb Sutter, Bjarne 的共识写法）。签名 `add(std::unique_ptr<Widget>)` 在调用点 `r.add(std::move(p));` 就能让读者立刻识别"所有权转给我了"；形参里再 `move` 一次几乎免费（unique_ptr 移动 = 复制一个指针 + 置空源）。
- **C 段（差）**：`&&` 只是写法噪声——按值接也强制 move（unique_ptr 不可拷贝），但 `&&` 还无法接受 `std::make_unique<Widget>()` 这种 prvalue 之外的复杂表达式（要看具体重载解析）。社区共识是按值版更简单、与重载/转发友好。
- **D 段（差）**：把 raw `new`/raw pointer 暴露在 API 上，调用方写 `r.add(new Widget(...));` 会在异常路径上泄漏（如果后续参数构造抛异常）；这正是 `make_unique` 要根除的反模式。

**核心识别点：**
- 表达"所有权转给我"：参数写 `std::unique_ptr<T>` **按值**，调用方写 `std::move`。
- `unique_ptr` 的"移动" = 复制 8 字节指针 + 置空源，几乎免费。
- 永远不要在 API 上写 `const unique_ptr<T>&`——要么 sink 按值接，要么 observe 传 `T*`/`T&`。
- 用裸 `new` 喂工厂的 API 在多参数下不异常安全；统一用 `make_unique`/`make_shared`。

**来源：** Herb Sutter "Leak-Freedom in C++" CppCon 2016；C++ Core Guidelines F.26/R.32；Effective Modern C++ Item 18/21。
