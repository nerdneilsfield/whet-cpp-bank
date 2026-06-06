---
qid: cpp-taste-param-008
type: single
kp: [cpp-memory-mgmt, cpp-functions]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: D
---

`render` 函数只想"看一眼" `Texture`、不在意所有权（不保存到任何成员）。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
void render(std::shared_ptr<Texture> t) {
    t->draw();
}
```

```cpp
// B
void render(const std::shared_ptr<Texture>& t) {
    t->draw();
}
```

```cpp
// C
void render(std::shared_ptr<Texture>&& t) {
    t->draw();
}
```

```cpp
// D
void render(const Texture& t) {
    t.draw();
}
```

A. A 段：按值接 `shared_ptr`，每次 +1/-1 引用计数，"线程安全最稳"。
B. B 段：`const&` 接 `shared_ptr`，避免引用计数原子操作，又能让调用方传 `shared_ptr`。
C. C 段：`&&` 表达"我可能要 sink"，最有未来扩展性。
D. D 段：函数只查看不存储，直接传 `const Texture&`，与所有权解耦。

## 解析

正确答案是 **D**。

- **A 段（差）**：按值接 `shared_ptr` = 一次原子 inc + 一次原子 dec，引用计数路径是已知的多线程伪共享重灾区；而且本函数根本不打算共享所有权，制造了一个"看起来要持有"的假信号。
- **B 段（差）**：避开了引用计数，但仍把 API 钉死在"调用方必须持有 `shared_ptr<Texture>`"上——如果调用方手头是 `Texture&`、`unique_ptr<Texture>`、栈对象，都没法用。这正是 Herb Sutter 称为"`shared_ptr` 污染"的现象。
- **C 段（差）**：`&&` 表示"我要 sink"，但本函数明明不存——意图错位；同时仍逼迫调用方持有 `shared_ptr`，把 B 的耦合问题和 sink 的语义混在一起。
- **D 段（好）**：`render` 不关心生命周期，应当把所有权问题留给调用方。`const Texture&`（或 `Texture&` / `Texture*`，看是否需要可变/可空）让函数复用面最大：栈对象、`unique_ptr` 的 `*p`、`shared_ptr` 的 `*p`、`Texture&` 都能传。这是 Core Guidelines R.36/R.30 的明确建议。

**核心识别点：**
- "只看不存"的参数：传 `T&` / `const T&` / `T*`，不传任何智能指针。
- `shared_ptr` 按值传 = 原子操作；`const shared_ptr<T>&` 仍把 API 钉死在 `shared_ptr` 上。
- 智能指针只在 API 表达"所有权语义"时出现：sink unique_ptr 表示"给你了"，sink shared_ptr 表示"分给你一份"。
- 不要让"我用 shared_ptr 管的"这种实现细节渗透到不关心生命周期的函数签名里。

**来源：** Herb Sutter GotW #91；C++ Core Guidelines R.30/R.34/R.36；Effective Modern C++ Item 19/41。
