---
qid: cpp-taste-init-015
type: single
kp: [cpp-cpp11, cpp-type-sizes]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, fixed-size-arrays]
---
要在函数内**栈上**保存最近 8 个 sensor 读数（每个是 `double`），并把它们做平均。大小在编译期就定（永远是 8）。四种容器选择哪个最有品味？

```cpp
// A
double readings[8];
for (int i = 0; i < 8; ++i) readings[i] = sample();
double sum = 0;
for (int i = 0; i < 8; ++i) sum += readings[i];
double avg = sum / 8;

// B
std::array<double, 8> readings;
for (auto& r : readings) r = sample();
double avg = std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size();

// C
std::vector<double> readings(8);
for (auto& r : readings) r = sample();
double avg = std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size();

// D
std::vector<double> readings;
readings.reserve(8);
for (int i = 0; i < 8; ++i) readings.push_back(sample());
double avg = std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size();
```

A. A — C 风格数组最快、零开销
B. B — `std::array<double, 8>` 编译期大小、STL 接口、栈上
C. C — `std::vector<double>(8)` 大小灵活、STL 标配
D. D — `reserve(8) + push_back` 最贴"逐步生成"的语义

---

**解析：**

选 B。这道题考 **"`std::array` 在编译期大小固定场景下是 `vector` 和 C 数组的双重替代品"** —— `array` 是 C++11 引入的、被严重低估的工具。

逐一品味：

- **A** **C 风格数组**：
  - 栈上、零开销、零分配 ✓
  - `sizeof(readings)` 在传给函数时**衰减成 `double*`**，size 信息丢失 ✗
  - 没有 `.begin()` / `.end()` —— 不能直接用 `std::accumulate`（要写 `readings, readings + 8`），不能 range-for（其实 C 数组可以 range-for，因为它有 size），但传到函数里就不行了
  - `int i = 0; i < 8; ++i` 的索引循环，是 C 时代写法，每次都要重复 `8` 这个魔数
  - **没有边界检查**、**不能赋值/拷贝/比较**
  
  适合极致 hot path 且性能 profile 过的场景；日常代码里看到 `T arr[N]` 应警觉。
- **B** **`std::array<double, 8>`**：
  - 栈上、零开销、零分配 ✓（和 C 数组等价的内存布局）
  - 编译期 size 是类型的一部分：`std::array<double, 8>` —— `.size()` 是 constexpr，**永远返回 8**
  - 完整 STL 接口：`begin/end/size/data/at/[]/fill/swap`，能 range-for、能传给 algorithm、能拷贝、能比较、能放进容器
  - 传给函数时**保留类型信息**：`void f(std::array<double, 8>&)` 编译期就知道大小
  - `readings.size()` 而不是魔数 8 —— 改成 16 只改类型那一处
  
  **零运行时代价，全套 STL 友好**。这就是 `std::array` 存在的理由。
- **C** **`std::vector<double>(8)`**：
  - **堆分配**——8 个 double 也要走 `new`/`malloc`，函数返回时 `delete`
  - 大小是 runtime 值，编译器不知道
  - 多一个间接（vector 在栈上是三个指针，data 在堆上）
  
  对一个**编译期就知道是 8 的小数组**用 vector 是用大炮打蚊子——付出堆分配代价换不到任何灵活性收益。
- **D** **`reserve(8) + push_back`**：
  - 同样堆分配（reserve 触发一次 `new`）
  - **push_back 比直接索引慢**：每次要检查 size < capacity（虽然编译器可能优化掉）、要更新 size、要构造 in-place
  - 表达上更"动态"——但你**完全知道**就是 8 个，伪装成"逐步生成"是噪音

`std::array<T, N>` 在 C++11 之前是空白——C++98 只能选 C 数组或 vector，于是 C 数组在嵌入式/性能敏感代码里大行其道。C++11 之后还在写 `T arr[N]` 大多是"没注意到 std::array 存在"。

**核心识别点**：

- **编译期大小** + **栈上** + **STL 接口** 三件套 = `std::array<T, N>`
- C 数组传给函数时**衰减成指针**，size 信息丢失（"array-to-pointer decay"），`std::array` 永不衰减
- `std::vector` 永远在堆上——即使 size 是 8——除非用了 small-vector optimization 的第三方库（`absl::InlinedVector` / `boost::small_vector`）
- `reserve + push_back` 适合**真的不知道最终大小**或**大小动态变化**，固定 8 元素硬要走 push_back 是过度抽象
- `std::array<T, N>` 的 `N` 是模板参数，编译期常量——可以用 `static_assert`、可以参与 SFINAE、可以传给 template 函数

`std::array` 还有一个被低估的特性：它支持 structured bindings（题12），可以写 `auto [x, y, z] = std::array{1, 2, 3};`。同样支持 CTAD（C++17）：`std::array{1.0, 2.0, 3.0}` 自动推导成 `std::array<double, 3>`。

一句话总结：**编译期已知大小 → `std::array`；运行时大小 → `std::vector`；C 数组只在和 C API 互操作时出现**。

**来源：** 手写题。`std::array` 见 ISO/IEC 14882:2011 §23.3.2 [array]；C++ Core Guidelines SL.con.1 "Prefer using STL `array` or `vector` instead of a C array"；Scott Meyers *Effective Modern C++* Item 12 / Item 13 中提到 `std::array` 在 size-known 场景下的优势。