---
qid: cpp-taste-init-001
type: single
kp: [cpp-cpp11, cpp-stl-basics]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, initialization]
---
要从 `int n = compute()` 的结果初始化一个 `std::vector<int>`，长度为 n、元素全为 0。四个写法功能"几乎"相同，哪个最有品味？

```cpp
// A
auto v = std::vector<int>(n);

// B
std::vector<int> v(n);

// C
std::vector<int> v{n};

// D
std::vector<int> v = std::vector<int>(n);
```

A. A — 用 `auto` 配合显式 `std::vector<int>(n)` 类型最清楚
B. B — 直接构造最简洁
C. C — 用统一初始化 `{}` 是现代 C++ 提倡的写法
D. D — 拷贝初始化语义最直白，类型出现两次也最不容易误读

---

**解析：**

选 B。这道题考的是 **"何时该用 `()`、何时该用 `{}`、何时该用 `auto`"** 的判断。

四个写法里只有 C 是**错的**——`std::vector<int> v{n}` 不是"长度 n 的 vector"，而是 **"含一个值为 n 的元素的 vector"**。这是 `vector` 的 `initializer_list` 构造函数优先于一般构造函数的著名陷阱（Scott Meyers *Effective Modern C++* Item 7）。所以 C 直接淘汰。

剩下 A、B、D 在语义上等价（都是 n 长 0 值），比的是品味：

- **A**：`auto v = std::vector<int>(n);` 这种写法在 Andrei Alexandrescu / Herb Sutter 的 "Almost Always Auto"（AAA）派系里是首选——左边永远是 `auto v = `，类型只写在右边一次，避免左右类型不一致。但放在这里**右边类型已经写了一次**、左边再写 `auto` 反而是把"`vector<int>` 这三个字符"用 4 个字符 + 一个 `=` 换来——没省事。AAA 的本意是消除冗余，不是凑形式。
- **B**：`std::vector<int> v(n);` 最直接：类型一次、构造一次、用 `()` 明确表达"调用大小构造函数而不是 initializer_list"。这是 C++ 自 1998 年起就正确的写法，**不会被 `{}` 的歧义咬到**。
- **D**：`std::vector<int> v = std::vector<int>(n);` 类型写两遍、还产生一个临时对象（虽然 C++17 后保证 copy elision、不会真拷贝），但**写法本身在传达一个错的信号**——"我在做拷贝初始化"。读者会以为你刻意要走拷贝路径（比如想触发某种转换），实际并没有。多余的视觉噪音。

**核心识别点**：

- 看见 `std::vector<T> v{n}` → 立即想到 **initializer_list 劫持** 陷阱
- 对**有 initializer_list 构造函数的容器**（vector、list、deque、map ...）：表达"大小/形状"用 `()`，表达"内容列表"用 `{}`
- AAA 风格的 `auto x = T(args)` 适合 **类型在右边不冗长**或 **想消除左右不一致风险**时；右边类型本就显式，左边再 auto 是凑形式
- 类型出现两次的初始化（`T v = T(args)`）在 C++17 之后没有任何性能成本，但**语义噪音**是真实的——读者会找你为什么要拷贝构造

`{}` 在 C++11 被设计为 "uniform initialization"——一统江湖的初始化。但 `vector` 这种 STL 容器为 initializer_list 重载了构造函数，导致 `{}` 在它们身上**反而不统一**。这是历史包袱，不是新人能避开的，只能记。

**来源：** 手写题。背景见 Scott Meyers *Effective Modern C++* Item 7 "Distinguish between () and {} when creating objects"；AAA 风格见 Herb Sutter "GotW #94: AAA Style"。
