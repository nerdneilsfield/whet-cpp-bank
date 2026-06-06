---
qid: cpp-perf-branch-004
type: single
kp: [cpp-polymorphism, cpp-cpp14-17]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: D
tags: [performance, code-taste]
---

要在循环里对 `std::vector<Shape>` 的几何对象（圆/方/三角）做面积累加，类型种类**固定 3 种**且全程已知。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
struct Shape { virtual double area() const = 0; virtual ~Shape() = default; };
struct Circle : Shape { double r; double area() const override { return 3.14*r*r; } };
struct Square : Shape { double s; double area() const override { return s*s; } };
struct Triangle: Shape { double b,h; double area() const override { return 0.5*b*h; } };
std::vector<std::unique_ptr<Shape>> shapes;
double s = 0; for (auto& p : shapes) s += p->area();

// B
struct Circle { double r; };
struct Square { double s; };
struct Triangle{ double b, h; };
using Shape = std::variant<Circle, Square, Triangle>;
std::vector<Shape> shapes;
double s = 0;
for (auto& sh : shapes)
    s += std::visit([](auto& x){
        if constexpr (std::is_same_v<decltype(x), Circle&>) return 3.14*x.r*x.r;
        else if constexpr (std::is_same_v<decltype(x), Square&>) return x.s*x.s;
        else return 0.5*x.b*x.h;
    }, sh);

// C
enum class Kind { Circle, Square, Triangle };
struct Shape { Kind k; double a, b; };
std::vector<Shape> shapes;
double s = 0;
for (auto& sh : shapes) {
    switch (sh.k) {
        case Kind::Circle:   s += 3.14*sh.a*sh.a; break;
        case Kind::Square:   s += sh.a*sh.a;     break;
        case Kind::Triangle: s += 0.5*sh.a*sh.b; break;
    }
}

// D
std::vector<double> circles_r;
std::vector<double> squares_s;
std::vector<std::pair<double,double>> tris_bh;
double s = 0;
for (double r : circles_r) s += 3.14*r*r;
for (double a : squares_s) s += a*a;
for (auto [b,h] : tris_bh) s += 0.5*b*h;
```

A. A — 标准面向对象多态，每种形状写自己的 area
B. B — std::variant + visit，类型安全且无虚函数
C. C — 用 enum 标签 + switch，避免虚函数
D. D — 按类型把形状分别放进三个 vector，三次纯循环

---

**解析：**

选 D。这道题考的是"动态 dispatch 的代价不仅是虚函数本身，还有它顺带杀掉的所有优化"。

逐一品味：

- **A**：① `vector<unique_ptr<Shape>>` 是**指针数组 + 堆分散对象**，每次 `p->area()` 先 load 指针、再 load vptr、再间接调用 area——三次依赖 load + 一次间接分支。② 间接分支预测器对随机类型分布命中率有限，每次 misprediction ~15 cycles。③ 每个 Shape 单独堆分配，内存随机，cache miss 严重。④ **完全禁止内联和向量化**——编译器看不到 area 内部。综合比 D 慢 **20–50 倍**。
- **B**：`variant` 把对象放栈/连续 vector 里，比 A 解决了堆分散和指针追逐。但 `std::visit` 内部仍是基于 `index()` 的间接跳转表，每次还有一次间接分支。混合类型遍历时编译器**无法把不同分支合并成 SIMD**——SIMD 要求循环体在多个迭代里是同一条指令。比 D 慢 **5–10 倍**。
- **C**：`switch on tag` 把间接分支降级成 ~3 路 jump table。比 A/B 都快——没有间接函数调用、对象连续。但同样的问题：循环里有 3 路分支，**SIMD 仍然不能跨类型展开**，相邻迭代可能走不同分支。比 D 慢 **3–5 倍**。
- **D**：按类型分桶后，**每个循环里所有元素同质**。编译器看 `for (double r : circles_r) s += 3.14*r*r` 时能直接展开成 SIMD（AVX2 4× double 同时算），还能软件流水。三个循环各自达到内存带宽峰值。零分支、零间接跳转、零虚函数。比 A 快 1–2 个数量级。这就是 Mike Acton 在 *Data-Oriented Design* 反复强调的"按类型分桶，把多态变成同质循环"——也是游戏引擎、ECS 框架的核心模式。

**核心识别点：**
- 看见 `vector<unique_ptr<Base>>` 做密集计算循环 → 警觉每个迭代是不是 3 次依赖 load + 间接 call + 阻断向量化
- 看见 `variant + visit` 用于循环里混合类型 dispatch → 比虚函数好但还是杀向量化
- 当类型种类**有限且编译时已知** → 按类型分桶（SoA-of-Types）总是更快
- 同质循环（一条指令在多元素上重复）才是 SIMD/流水线/预取器的最爱
- 多态的真正代价不是间接 call 的 ~5 cycles，而是它**禁用了内联和向量化**这两个数量级的优化

**来源：** Mike Acton, "Data-Oriented Design and C++", CppCon 2014；Stoyan Nikolov, "OOP Is Dead, Long Live Data-oriented Design", CppCon 2018；Andrei Alexandrescu, "Optimization Tips", code::dive.
