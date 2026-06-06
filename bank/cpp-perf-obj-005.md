---
qid: cpp-perf-obj-005
type: single
kp: [cpp-functions, cpp-lambdas, cpp-templates]
primary_kp: cpp-functions
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要在 1 千万次循环里对每个元素应用一个用户传入的小函数（如 `x*2+1`）。下面四种接口设计功能等价，哪个最值得采用？

```cpp
// A
template<class F>
void apply(std::vector<double>& v, F f) {
    for (double& x : v) x = f(x);
}
// 调用: apply(v, [](double x){ return x*2 + 1; });

// B
void apply(std::vector<double>& v, std::function<double(double)> f) {
    for (double& x : v) x = f(x);
}
// 调用: apply(v, [](double x){ return x*2 + 1; });

// C
void apply(std::vector<double>& v, double (*f)(double)) {
    for (double& x : v) x = f(x);
}
// 调用: apply(v, [](double x){ return x*2 + 1; });

// D
struct Op { virtual double operator()(double) const = 0; virtual ~Op() = default; };
void apply(std::vector<double>& v, const Op& f) {
    for (double& x : v) x = f(x);
}
// 调用: class MyOp : public Op { double operator()(double x) const override { return x*2+1; } }; apply(v, MyOp{});
```

A. A — 模板参数 F 接收任意可调用对象
B. B — std::function 类型擦除，接口统一
C. C — C 风格函数指针，最简单的类型
D. D — 抽象基类 + virtual operator()，OO 风格

---

**解析：**

选 A。这道题考的是"类型擦除（std::function、虚函数、函数指针）vs 模板内联"的性能差异。

逐一品味：

- **A**：模板 `F` 在调用点单独实例化——`apply<lambda类型>(v, lambda)`。编译器看得见 lambda 的 `operator()` 内部代码，**完全内联**：循环退化成 `for (x : v) x = x*2 + 1`，然后向量化 + 展开。**和把 lambda 体直接写在循环里完全一样**——零抽象代价。这就是 STL 算法（`std::transform`、`std::sort` 比较器）能保持高性能的根本原因。
- **B**：`std::function` 是类型擦除容器，内部用 vptr + 堆分配（lambda 大于 small buffer 时）实现"接受任意可调用"。每次 `f(x)` 走**一次间接调用**（约 5 cycles + 间接分支预测开销 0–15 cycles），**完全阻断内联和向量化**。1e7 次调用 ≈ 50–200ms vs A 的几 ms。比 A 慢 **10–50 倍**。Chandler Carruth 在 CppCon 多次以此作为"抽象有代价"的标杆例子。
- **C**：函数指针调用是一次间接调用（**通过指针 jmp**），LLVM/GCC 在简单情况下能做 indirect call promotion（PGO 时）猜测最常见目标后内联，但默认不行。**阻断内联和向量化**。比 A 慢 **5–20 倍**。此外，C 不能接收带捕获的 lambda（只能接收 non-capturing）。
- **D**：虚函数 = vptr 间接调用 + 阻断内联 + 每个实例多 8 字节 vptr。性能和 B 接近，**比 A 慢 10–50 倍**。OO 风格的优雅完全不抵这两个数量级的代价。

A 在编译期把"f 是什么"具象化，编译器看见整个调用链，**抽象在编译期消解**。这就是 Stepanov/Stroustrup 设计 STL 算法时坚持模板而非虚函数/函数指针的关键决策——"模板让抽象零代价"。

**核心识别点：**
- 看见热路径里调用 `std::function` → 警觉是不是在用类型擦除付间接调用 + 阻断内联的代价
- 看见"为了接口统一"用虚函数/std::function → 警觉是不是把编译期能解决的事推到了运行期
- 模板传可调用对象（如 STL 算法做的）= 抽象零代价
- 间接调用阻断内联，进而阻断常量传播、循环不变量提取、向量化——**连锁性能损失**
- 高性能循环里调用 lambda：用模板参数；只是配置/回调注册才用 std::function

**来源：** Chandler Carruth, "Efficiency with Algorithms, Performance with Data Structures", CppCon 2014；Andrei Alexandrescu, "Type Erasure", code::dive；Stepanov & McJones, "Elements of Programming"（关于 STL 设计的注脚）.

## Explanation

选 A，因为模板可调用对象让 lambda 类型在编译期可见，循环里的调用可完全内联并继续向量化。`std::function`、函数指针和虚函数都会引入间接调用，阻断内联和常量传播。误区是只追求统一接口，却把热路径上的零成本抽象变成运行时分派。
