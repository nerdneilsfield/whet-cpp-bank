---
qid: cpp-taste-init-005
type: single
kp: [cpp-cpp14-17, cpp-cpp11]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, initialization, constexpr]
---
要声明一个**程序启动时就有确定值、整个生命周期不变、可被多个翻译单元在 static initialization 阶段安全读取**的全局查表数组（含 256 个 `unsigned char`）。哪个声明最有品味？

```cpp
// A
const std::array<unsigned char, 256> table = make_table();

// B
constexpr std::array<unsigned char, 256> table = make_table();

// C
const std::array<unsigned char, 256> table = []{
    std::array<unsigned char, 256> t{};
    for (int i = 0; i < 256; ++i) t[i] = i ^ 0xAA;
    return t;
}();

// D
constinit const std::array<unsigned char, 256> table = []{
    std::array<unsigned char, 256> t{};
    for (int i = 0; i < 256; ++i) t[i] = i ^ 0xAA;
    return t;
}();
```

A. A — `const` + 工厂函数，最普通也最稳
B. B — `constexpr` 保证编译期求值，最强
C. C — 用 IIFE lambda 当工厂，避免外面定义 `make_table`，自包含
D. D — `constinit const` 静态初始化 + 不可变，最贴需求

---

**解析：**

选 D。这道题考 **"`const` / `constexpr` / `constinit` 三个关键字描述的是不同维度的约束"**，新人常以为它们是同义词的强弱版本。

三个关键字管的事完全不同：

| 关键字 | 管什么 |
|--------|--------|
| `const` | **不可被修改**（运行时只读） |
| `constexpr` | **可以在编译期求值**（隐含 const，但不要求一定在编译期求） |
| `constinit`（C++20） | **必须在静态初始化阶段完成初始化**（避开 dynamic initialization、避开 "static initialization order fiasco"） |

题目要求三件事：
1. **程序启动时就有确定值** → 要 `constinit` 或 `constexpr`（保证 static initialization，避开 SIOF）
2. **整个生命周期不变** → 要 `const`
3. **可被多个 TU 安全读取** → 要 `constinit` 或 `constexpr`（dynamic initialization 在跨 TU 顺序不定的情况下不安全）

逐一品味：

- **A**：`const + make_table()` ——`make_table()` 是普通函数调用，**走 dynamic initialization**。在多 TU 场景下触发经典的 **static initialization order fiasco**：另一个 TU 的全局对象在构造时若读 `table`，可能读到全零（未初始化）。"const" 只保证写不进，不保证什么时候初始化。
- **B**：**编不过**。`constexpr` 要求初始化器是**常量表达式**，而 `make_table()` 没标 constexpr。即使标了 constexpr，`std::array` 在 C++17/20 是 literal type、可以 constexpr，但 `make_table` 的实现也要全程 constexpr 才行。再者 `constexpr` 隐含 const，所以 B 如果改成 `constexpr ... = make_table_constexpr()` **就和 D 几乎等价**——但题目给的 `make_table()` 不是 constexpr 的，B 就是错的。
- **C**：IIFE（immediately-invoked function expression）lambda 写得很漂亮——自包含、无外部依赖。但 lambda 的 `operator()` **默认不是 constexpr**（C++17 起若 body 满足 constexpr 条件会**隐式** constexpr），更关键的是 **`const ... = []{...}()`** 这个赋值的求值时机是 dynamic initialization。和 A 同病——SIOF 风险。**写得现代化不等于初始化时机正确**。
- **D**：`constinit` 是 C++20 专为"静态初始化不要走运行时"设计的关键字。它**强制**编译期/静态初始化（如果做不到就编译错误，不会偷偷退化成 dynamic）。再叠加 `const` 表达"运行时不可修改"。一个 lambda 满足"所有用到的操作都是 constexpr-friendly"时，`constinit` 就能在编译期把表算好填进 `.rodata`，根本不在运行时构造。

`constinit const` ≠ `constexpr` 的原因：`constexpr` 要求该**变量本身**可以出现在常量表达式里（比如 `template<int N>` 的 N），`constinit` 只管初始化时机、不要求变量本身能用在常量表达式里。题目要求"启动时有确定值",这是初始化时机问题、不是"我要在模板参数里用它"——精确匹配 `constinit`。

**核心识别点**：

- 全局/静态变量初始化看见 **普通函数调用** → 警觉 dynamic init / SIOF
- 看见 `const T x = f();` 在全局作用域 → 想想 f 是不是 constexpr，不是的话有 SIOF 风险
- C++20 之后 `constinit` 是表达"我要静态初始化"的最精确工具，比 `constexpr` 弱一档但更聚焦
- IIFE lambda 是好工具，但**不会自动让初始化变成编译期**，要看 lambda 体能不能 constexpr
- `const` / `constexpr` / `constinit` 三正交：分别管"不可改"、"编译期可求值"、"静态初始化"

老一辈 C++ 程序员习惯把 SIOF 用 "Construct On First Use" idiom（函数内 static 局部变量）解决——但那要付出每次调用一次 `if (initialized)` 的代价。`constinit` 把这个问题从运行时检查推到编译期保证，是 C++20 一个安静但根本性的改善。

**来源：** 手写题。`constinit` 见 ISO/IEC 14882:2020 §9.2.9.4 [dcl.constinit]；SIOF 经典讨论见 Scott Meyers *Effective C++* Item 4 "Make sure objects are initialized before they're used"；C++ Core Guidelines I.22 "Avoid complex initialization of global objects"。

## Explanation

正确答案是 D。写得现代化不等于初始化时机正确。
在多 TU 场景下触发经典的 static initialization order fiasco：另一个 TU 的全局对象在构造时若读 `table`，可能读到全零（未初始化）。
这道题考 "`const` / `constexpr` / `constinit` 三个关键字描述的是不同维度的约束"，新人常以为它们是同义词的强弱版本。
