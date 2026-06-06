---
qid: cpp-perf-inline-002
type: single
kp: [cpp-polymorphism, cpp-templates, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要写一个"形状面积计算"工具，**面积函数会被密集循环调用**，形状种类在编译期已知（这个 .cpp 里只处理 `Circle`）。下面四种实现功能等价，哪个最值得采用？

```cpp
// A
struct Shape { virtual double area() const = 0; virtual ~Shape() = default; };
struct Circle : Shape { double r; double area() const override { return 3.14*r*r; } };
double total(const std::vector<Shape*>& v) {
    double s = 0;
    for (auto* p : v) s += p->area();
    return s;
}

// B
struct Shape { virtual double area() const = 0; virtual ~Shape() = default; };
struct Circle final : Shape { double r; double area() const final { return 3.14*r*r; } };
double total(const std::vector<Circle*>& v) {
    double s = 0;
    for (auto* p : v) s += p->area();
    return s;
}

// C
template<class S> struct Shape { double area() const { return static_cast<const S*>(this)->area_impl(); } };
struct Circle : Shape<Circle> { double r; double area_impl() const { return 3.14*r*r; } };
double total(const std::vector<Circle>& v) {
    double s = 0;
    for (auto& c : v) s += c.area();
    return s;
}

// D
struct Shape { virtual double area() const = 0; virtual ~Shape() = default; };
struct Circle : Shape { double r; double area() const override { return 3.14*r*r; } };
double total(const std::vector<std::unique_ptr<Shape>>& v) {
    double s = 0;
    for (auto& p : v) s += p->area();
    return s;
}
```

A. A — 经典虚函数 + 指针 vector
B. B — 用 final 标记 + 调用方知道是 Circle*，编译器可 devirtualize
C. C — CRTP 模板继承，静态多态
D. D — unique_ptr 拥有 Shape，最常见的 OOP 模式

---

**解析：**

选 C。这道题考的是"动态/静态多态、devirtualization 的可触发条件"。

逐一品味：

- **A**：`p->area()` 是虚函数调用——load vptr、load vtable 槽、间接 call。编译器看不到 area 实现（即使 `final` 也不可能，因为 Shape* 类型）。**无法内联**，每次 ~5 cycles 间接调用 + 阻断常量折叠和向量化。
- **B**：表面上 `Circle` 和 `area` 都标了 `final`，加 `vector<Circle*>` 类型，编译器有可能 devirtualize（直接调用 `Circle::area`，跳过 vtable）。**但实际上**：① 编译器对"通过基类指针调用，静态类型 = Circle*"的 devirtualization 不一定触发——GCC `-fdevirtualize-speculatively` + LTO 才可靠；② 即便 devirtualize 后仍是 direct call，没有内联。需要再加 `area` 的定义可见才能内联。**部分改善，但脆弱、依赖编译器版本**。
- **C**：CRTP（Curiously Recurring Template Pattern）—— `Shape<Circle>::area()` 在编译期就调用 `Circle::area_impl()`，**全部 static call，可内联，零间接跳转**。`vector<Circle>` 是值容器、内存连续，循环里 `c.area()` 内联展开成 `3.14*r*r`，进一步可向量化。**比 A/D 快 10–50 倍**。这是当"类型在编译期已知"时取代虚函数的标准做法（Eigen、Boost.GIL、CGAL 大量使用）。
- **D**：在 A 的基础上再加 `unique_ptr` 间接 + 堆分散的对象内存——内存访问也变随机，**雪上加霜**。比 A 还慢。

C 优于 B 的关键：B 的 devirtualization 是脆弱的"编译器或许做得到"，C 的静态多态是**语言层面保证**。何况 C 把内存布局也修了（`vector<Circle>` 连续 vs `vector<Shape*>` 间接）。

**核心识别点：**
- 看见"编译期已知类型的虚函数调用" → 警觉 CRTP 能把它静态化
- 看见 `final` 关键字 → 知道它能帮助但不保证 devirtualize，且不能替代内联
- 看见 `vector<Base*>`/`vector<unique_ptr<Base>>` 用于密集循环 → 警觉间接 + 阻断内联 + 阻断 SIMD
- CRTP 在编译期已知类型时是"虚函数 + 内联"的等效替代，零运行时代价
- devirtualization 的触发条件挑剔：final + LTO + 静态类型可见——不要赌编译器

**来源：** Andrei Alexandrescu, "Modern C++ Design", §1.4 "Policy-based design"；Chandler Carruth, "Going Nowhere Faster", CppCon 2019；Eigen 文档 "Why Eigen uses expression templates".
