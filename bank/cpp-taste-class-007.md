---
qid: cpp-taste-class-007
type: single
kp: [cpp-classes, cpp-cpp11, cpp-move-semantics]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, type-erasure]
---
需要设计一个"可排序的数据源"接口——只有一个操作 `int key() const`。四个设计哪个品味最好？

```cpp
// A — 纯虚基类
class Sortable {
public:
    virtual int key() const = 0;
    virtual ~Sortable() = default;
};

// B — std::function 类型擦除
class Sortable {
public:
    template<typename T>
    explicit Sortable(T obj) : impl_(std::make_shared<Model<T>>(std::move(obj))) {}
    int key() const { return impl_->key(); }
private:
    struct Concept {
        virtual int key() const = 0;
        virtual ~Concept() = default;
    };
    template<typename T>
    struct Model : Concept {
        explicit Model(T obj) : data_(std::move(obj)) {}
        int key() const override { return data_.key(); }
        T data_;
    };
    std::shared_ptr<const Concept> impl_;
};

// C
using Sortable = std::function<int()>;

// D — variant + visit
template<typename... Ts>
using Sortable = std::variant<Ts...>;
```

A. A — 经典 OOP 接口，每个子类继承并实现 key()，最正统
B. B — 类型擦除，支持任意满足 key() 的类型而不需要继承，最灵活
C. C — Sortable 就是一个 `std::function<int()>`，调用方传入 lambda/bind 即可，最简单
D. D — variant 编译期多态，零运行时开销

---

**解析：**

选 C。这题考的是**"接口真的有必要是类吗？"**——当接口只有一个函数时，函数类型就是最好的接口。

逐一品味：

- **A**：纯虚基类引入了一整套运行时多态机制：虚表、RTTI、堆分配（至少通过指针引用）。然而底层需求仅仅是"一个能返回 int 的操作"。`virtual ~Sortable()` 必须正确（否则多态 delete UB），派生类必须公开继承——这是用**大炮打蚊子**。15 行基础设施只为了一行 `int key()`。
- **B**：经典的类型擦除（Type Erasure）模式——`std::function` 内部就是这种实现的变体。但同样的问题：为了一个单操作，引入了虚表 + shared_ptr + Concept/Model 两层结构。除非你真的需要在同一个容器里存 A 类型和 B 类型（它们全是不同的类但都 `.key()`），否则这个复杂度不必要。B 在 "any" 场景下是正确答案，但在只需要 "int 一个值" 的场景下太重。
- **C**：`std::function<int()>` 是最轻量的抽象。"可排序的数据源"本质上就是"一个能告诉我排序键的 callable"。调用方传 lambda（捕获任意对象）、bind、或者函数指针都可以。不需要继承体系、不需要虚表、不需要类型擦除。**当需求是一个函数时，就用一个函数类型来表达接口。**
- **D**：`variant` 在编译期展开所有可能类型，没有虚表开销。但这里的问题是：`variant<Ts...>` 要求**在定义 Sortable 时就知道所有可能的类型**。在很多场景下这是做不到的（插件式架构、用户自定义类型）。而且 `Sortable` 现在是模板别名而非类型，不能用在运行期多态容器中。

C 胜出的理由很关键：**`std::function<int()>` 作为接口比类接口更轻、更灵活**。它接受 lambda、成员函数指针、仿函数、bind 表达式。调用方不需要引入任何继承关系。这是现代 C++ "基于概念而非继承"的设计思路的体现。

但注意 C 的适用范围：如果接口需要多个操作（比如 `key()` 和 `value()` 和 `hash()`），C 就不合适了——那时类型擦除（B）或纯虚（A）才是更好的选择。

**核心识别点**：
- 一个函数的接口 → `std::function` 比纯虚类更轻
- 纯虚基类引入虚表 + RTTI + heap 分配，小接口下代价高
- variant 需要编译期知道所有类型，不是运行时多态的替代
- "类型擦除" 是在真的需要 type-erased container 时的方案，不是默认选择

**来源：** 手写题。Sean Parent "Inheritance Is The Base Class of Evil" (C++Now 2013) 关于类型擦除的讨论；C++ Core Guidelines I.5: "Prefer compile-time polymorphism to run-time polymorphism"。