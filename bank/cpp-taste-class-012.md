---
qid: cpp-taste-class-012
type: single
kp: [cpp-classes, cpp-cpp11, cpp-move-semantics]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, polymorphism]
---
需要表达"形状"（Circle、Square、Triangle），提供统一的 `area()`。已知形状类型集合**固定且封闭**。哪个设计品味最好？

```cpp
// A — CRTP
template<typename Derived>
class Shape {
public:
    double area() const { return static_cast<const Derived*>(this)->area_impl(); }
};
class Circle : public Shape<Circle> {
    double r_;
public:
    double area_impl() const { return 3.14159 * r_ * r_; }
};

// B — 运行时多态
class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
    double r_;
public:
    double area() const override { return 3.14159 * r_ * r_; }
};
// std::vector<std::unique_ptr<Shape>> shapes;

// C — std::variant + visit
struct Circle { double r; };
struct Square { double side; };
struct Triangle { double base, height; };
using Shape = std::variant<Circle, Square, Triangle>;

double area(const Shape& s) {
    return std::visit([](const auto& shape) -> double {
        if constexpr (std::is_same_v<std::decay_t<decltype(shape)>, Circle>) {
            return 3.14159 * shape.r * shape.r;
        } else if constexpr (std::is_same_v<std::decay_t<decltype(shape)>, Square>) {
            return shape.side * shape.side;
        } else {
            return 0.5 * shape.base * shape.height;
        }
    }, s);
}

// D — 自己手写类型标记
struct Shape {
    enum Type { CIRCLE, SQUARE, TRIANGLE } type;
    union { struct {double r;} circle; struct {double side;} square; struct {double b, h;} tri; };
};
```

A. A — CRTP 编译期多态，零虚函数开销
B. B — 经典 OOP，最直观、最教科书
C. C — variant + visit，编译期多态、值语义、类型安全、封闭集合的天然表达
D. D — 手写 tagged union，最贴近底层

---

**解析：**

选 C。这道题考**"封闭类型集合"的最佳建模工具**。

逐一品味：

- **A**：CRTP 的核心用途是**给基类提供静态多态接口**——但 CRTP 要求 `Shape<Circle>` 和 `Shape<Square>` 是不同类型，**无法放在同一个容器里**。如果你要 `vector<Shape>` 存各种形状，CRTP 失效。CRTP 适合"接口注入"（如 `enable_shared_from_this`），不适合"形状集合"场景。
- **B**：运行时多态的经典方案。优点：可以放进 `vector<unique_ptr<Shape>>`、添加新形状只需新派生类。**但代价**：每个对象需要 vptr（指针大小开销）、虚调用不能 inline、堆分配（unique_ptr）、值语义丢失。在**类型集合封闭**的情况下，这些代价没有相应的灵活性回报——你不需要"未来可能添加新形状"这种开放性。
- **C**：variant + visit。优点：**变种集合在类型中显式声明**（编译器知道全集），visit 编译期分派（潜在 inline），**值语义**（可以放 `vector<Shape>`，无 unique_ptr 包装），栈分配，**穷举性检查**（如果 visit 的 lambda 漏处理某个类型，编译错误）。`if constexpr` + `decltype` 处理每种类型的具体逻辑。对**封闭集合**这是最现代、最 C++17 的表达。
- **D**：手写 tagged union——**复刻了 variant 的所有缺点而没有它的安全性**。手动检查 `type` 字段、忘记处理某个 case 编译器不会警告、union 的字段不是 trivial 时需要手动调用构造/析构。这是 1990 年代的 C 写法，C++ 给了你 variant 就别再手写了。

C 胜出的关键：当**变种集合是封闭的且确定的**，编译期穷举性检查是巨大的安全保证。继承体系做不到这一点（任何人可以再派生一个新 Shape）。variant 把"可能的形状"硬编码在类型中，**编译器替你检查 visit 是否完备**。

**核心识别点**：
- 开放类型集合（未来可能新增）→ 虚函数继承
- 封闭类型集合 → variant + visit
- 需要值语义（拷贝/移动/容器存储无 ptr 包装）→ variant
- CRTP 适用于"基类提供静态接口"，不适用于"运行时存异类对象"
- 手写 tagged union → 总是劣于 variant

**来源：** 手写题。C++17 variant + visit；Sean Parent "Better Code: Runtime Polymorphism" (NDC 2017)。

## Explanation

正确答案是 C。这道题考"封闭类型集合"的最佳建模工具。
手动检查 `type` 字段、忘记处理某个 case 编译器不会警告、union 的字段不是 trivial 时需要手动调用构造/析构。
但代价：每个对象需要 vptr（指针大小开销）、虚调用不能 inline、堆分配（unique_ptr）、值语义丢失。
