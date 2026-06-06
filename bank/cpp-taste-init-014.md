---
qid: cpp-taste-init-014
type: single
kp: [cpp-cpp11, cpp-type-sizes]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, auto-deduction]
---
要遍历 `std::vector<std::string> names` 把每个元素传给 `process(const std::string&)`。四种 range-for 写法哪个最有品味？

```cpp
// A
for (auto x : names) process(x);

// B
for (auto& x : names) process(x);

// C
for (const auto& x : names) process(x);

// D
for (auto&& x : names) process(x);
```

A. A — 按值最简洁
B. B — 按引用避免拷贝
C. C — `const auto&` 表达"只读引用"
D. D — `auto&&` 是 forwarding reference 最通用，能绑左右值

---

**解析：**

选 C。这道题考 **`auto`/`auto&`/`const auto&`/`auto&&` 四种 range-for 引用形态对应的语义选择**，新人和老手都常混淆。

逐一品味（这里假设循环体只调用 `process(x)`，不修改 x）：

- **A** `auto x : names` ：**每轮拷贝一个 `std::string`**。对 `string` 是一次堆分配 + memcpy（除非 SSO 命中）。`names` 有 100 个元素就 100 次拷贝。如果 `process` 自己只读 x，这些拷贝纯粹是浪费。**这是"我懒得想类型"的代价**。
- **B** `auto& x : names` ：**非 const 引用**——零拷贝，能改。但你**根本不打算改**，写 `auto&` 是在向读者承诺"我可能会改"，读者要花精力扫整个循环体确认你没改。**信号过强**。也容易被误用：以后维护者读到 `auto& x` 会以为 "改 x 是预期行为"，可能真就改了。
- **C** `const auto& x : names` ：**精确表达**：
  - 零拷贝（`&`）
  - 不修改（`const`）
  - `auto` 让类型跟着容器走（容器换成 `vector<MyClass>` 不用改循环）
  
  这是 range-for 只读遍历的**默认选择**。每个修饰符都有目的，每个都不能省。
- **D** `auto&& x : names` ：**forwarding reference**（也叫 universal reference）。能绑左值也能绑右值。对 `vector<string>`：`*it` 是 lvalue → `auto&&` 推导为 `std::string&`，**和 B 等价**。所以 D 在 B 的场景下**没有任何额外优势**，反而：
  - `&&` 让读者以为你打算 `std::move(x)`，要去做"消费 + 移动"的事
  - 在**不是真的 forwarding**的场景用 forwarding reference 是噪音

  `auto&& x` 的合理场景是**模板里、或者容器返回 proxy 类型**（比如 `vector<bool>::reference`、`std::ranges::views::xxx` 返回的 prvalue）。对普通 `vector<string>`，`const auto&` 总是更好。

四种写法的"品味矩阵"：

| 写法 | 拷贝 | 可改 | 信号 | 何时用 |
|------|------|------|------|--------|
| `auto x` | 是 | 自身可改 | "我要独立副本" | 真的需要副本（要 move 走、要修改不影响原对象） |
| `auto& x` | 否 | 是（改原对象） | "我会改 names 的元素" | 真的要修改容器元素 |
| `const auto& x` | 否 | 否 | "我只读" | **只读遍历的默认** |
| `auto&& x` | 否 | 视情况 | "我可能 forward / move" | 模板代码 / 容器返回 proxy(`vector<bool>`、views) |

**核心识别点**：

- range-for 的引用形态承载语义信号——选错就误导读者
- `const auto&` 是"只读"的诚实写法，是 90% range-for 场景的正确答案
- `auto&&` 不是"通用更好"——在普通容器上和 `auto&` 等价但信号错
- 遍历 `vector<bool>` 时**必须**用 `auto&&`（`vector<bool>::reference` 是 proxy）
- 看到 `auto x : container` 且 container 元素是非平凡类型（string/vector/...）→ 警觉性能
- `auto& x` 用于"我真的要改这个元素"的场景，别用作通用别名

`auto&&` 在 C++ ranges (C++20) 里变得更重要——`views::transform` / `views::filter` 这些产生的视图可能 yield prvalue，用 `auto&` 接不上、用 `const auto&` 浪费一个临时的生命周期延长，**`auto&&` 才是兜底正确**。但仅在那个场景下推荐——日常 STL 容器遍历仍然是 `const auto&`。

Herb Sutter "GotW #93: Auto Variables, Part 2" 的口诀：

> **Use `const auto&` by default; `auto&` when you need to modify; `auto` when you need a copy; `auto&&` when you write generic code.**

**来源：** 手写题。forwarding reference 见 Scott Meyers *Effective Modern C++* Item 24-25；range-for 引用形态见 Herb Sutter "GotW #93"、Item 7 of *Effective Modern C++*；`vector<bool>` proxy 问题见 Item 6。

## Explanation

正确答案是 C。这道题考 `auto`/`auto&`/`const auto&`/`auto&&` 四种 range-for 引用形态对应的语义选择，新人和老手都常混淆。
工程上要理解现代 C++ 语法背后的推导、重载和生命周期规则，而不是只按表面写法判断。
也容易被误用：以后维护者读到 `auto& x` 会以为 "改 x 是预期行为"，可能真就改了。
