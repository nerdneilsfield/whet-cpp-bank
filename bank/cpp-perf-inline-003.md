---
qid: cpp-perf-inline-003
type: single
kp: [cpp-functions, cpp-classes]
primary_kp: cpp-functions
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要在 1e9 次循环里检查 `x < threshold` 并把 `x` 累加到 sum。下面四种封装功能等价，哪个最值得采用？

```cpp
// A
long sum = 0;
for (int x : data)
    if (x < threshold) sum += x;

// B
struct Checker {
    int threshold;
    inline bool ok(int x) const { return x < threshold; }
};
Checker c{threshold};
long sum = 0;
for (int x : data)
    if (c.ok(x)) sum += x;

// C
struct IChecker { virtual bool ok(int x) const = 0; virtual ~IChecker() = default; };
struct LessChecker : IChecker {
    int threshold;
    bool ok(int x) const override { return x < threshold; }
};
LessChecker lc{threshold};
IChecker& c = lc;
long sum = 0;
for (int x : data)
    if (c.ok(x)) sum += x;

// D
std::function<bool(int)> ok = [threshold](int x){ return x < threshold; };
long sum = 0;
for (int x : data)
    if (ok(x)) sum += x;
```

A. A — 直接把比较写在循环里
B. B — 把比较封装成小成员函数，标 inline
C. C — 用抽象接口 + 派生类实现，可替换策略
D. D — 用 std::function 持有 lambda，最灵活

---

**解析：**

选 A。这道题考的是"抽象的运行时代价"——B 看起来"应该内联"，实测和 A 一样，但 A 更直白；C/D 是数量级的代价。

逐一品味：

- **A**：循环体内联展开 → `cmp + cmov` 或者带分支累加，编译器进一步识别为条件 reduction，配合 AVX2 `vpcmpgtd + vpand + vpaddd` 一条指令处理 8 个 int。**最简、最快，循环体完全透明给编译器**。
- **B**：`Checker::ok` 定义在头里，`inline` 关键字 + 函数体可见 → 编译器内联。**生成代码理论上和 A 等价**。但代价：① 多写 5 行；② 增加抽象层，未来若 ok 被改成虚函数或迁到 .cpp，性能直接掉到 C 级别。**性能 = A，代码冗余**。看似"封装更工程"，对这种一行比较是过度抽象。
- **C**：虚函数 `c.ok(x)` —— `c` 是 `IChecker&`，编译器**无法 devirtualize**（基类引用静态类型）。每次循环里一次间接函数调用 + 一次返回，阻断内联与向量化。比 A 慢 **10–30 倍**。本想要"未来可换策略"，但**真正需要换时再加抽象**，"以防万一的虚函数"是经典反模式。
- **D**：`std::function` 调用每次是 vptr 间接调用 + 可能的小缓冲优化判断，阻断内联和向量化。比 A 慢 **10–50 倍**。lambda 本身的捕获也带类型擦除开销。

A 优于 B 不在性能（一样）而在**避免不必要的抽象**——一行比较不需要类。代码读起来"sum += x if x < threshold"一眼看完，没有"先去找 Checker 看 ok 是啥"的间接。Carruth 的口头禅：*"Abstraction has cost. Even when zero-cost in CPU cycles, it costs cognitive load."*

**核心识别点：**
- 看见"为一行逻辑建一个类/接口/函数对象" → 警觉是不是过度抽象，让读者多跳一次定义
- 看见 `std::function` 在密集循环 → 几乎一定是间接调用 + 阻断内联
- 看见用基类引用调用虚函数（即使 final）→ devirtualization 不可靠
- 抽象的代价分两层：① 运行时（间接调用、阻断内联）；② 认知（多一层跳转才能理解）
- A 的"直接写"在循环规模 N 大时，仍是最优解；只有重复多次相同模式时才提取抽象

**来源：** Chandler Carruth, "There Are No Zero-cost Abstractions", CppCon 2019；Sean Parent, "C++ Seasoning", GoingNative 2013（"no raw loops" 与 "no unnecessary abstraction" 的张力）；Kent Beck, "Smalltalk Best Practice Patterns"（"Inline" pattern）.

## Explanation

正确答案应把小而频繁调用的逻辑放在编译器可见的位置。头文件模板、constexpr 或普通内联函数能保留零成本抽象；跨翻译单元且没有 LTO 时，优化器往往看不到函数体。误区是为“封装”把热循环中的微操作藏到无法内联的接口后面。
