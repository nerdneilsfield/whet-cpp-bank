---
qid: cpp-taste-class-010
type: single
kp: [cpp-classes, cpp-cpp11]
primary_kp: cpp-classes
difficulty: hard
answer_key: A
tags: [code-taste, best-practice, encapsulation]
---
定义一个 `Point2D` 类（表示 2D 平面上的点）。哪个设计品味最好？

```cpp
// A
struct Point2D {
    double x;
    double y;
};

// B
class Point2D {
    double x_, y_;
public:
    Point2D(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }
    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }
};

// C
class Point2D {
    double x_, y_;
public:
    Point2D(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }
    double& x() { return x_; }
    double& y() { return y_; }
};

// D
class Point2D {
    double data_[2];
public:
    Point2D(double x, double y) : data_{x, y} {}
    double x() const { return data_[0]; }
    double y() const { return data_[1]; }
};
```

A. A — 简单的 struct + 公有成员，对 "纯数据" 类型最地道
B. B — 完整封装：私有字段 + getter/setter
C. C — 返回引用，可以用作 lvalue（`p.x() = 3.0`）
D. D — 内部用数组存，更紧凑且可以下标访问

---

**解析：**

选 A。这道题考的是**"封装" 不是教条，识别"纯数据类型"和"行为类型"是基本功**。

逐一品味：

- **A**：Point2D 是**值聚合体**——它没有不变量（x 和 y 可以是任意值），没有内部状态需要维护，没有需要禁止的操作。对这种类型，`struct` + 公有成员是最诚实的设计。**没有任何隐藏的复杂度**：构造、拷贝、移动、聚合初始化 `{1.0, 2.0}` 全部正确。C++ Core Guidelines 明确指出：当所有成员都可以独立变化且不维护不变量时，用 struct。
- **B**：把每个字段封装成 `get/set` 对——**100% 的样板代码**。`p.x()` 和 `p.x_` 在功能上完全等价，但前者每次写要 4 个字符多。getter/setter 的合理性在于：(1) 想加日志/校验、(2) 想未来改实现而不破坏接口。对 Point2D 这种纯数据类型，两个理由都不成立。这是 Java/C# 风格的"反射式封装"，在 C++ 里是**反模式**。
- **C**：返回引用让 `p.x() = 3.0` 能 work——但这等于绕了一大圈最终回到了 `p.x` 的语义，只是现在多了几个字符。**封装的全部意义是隐藏内部表示**，而 C 通过返回引用把内部表示彻底暴露了。比 B 更糟，因为 B 至少阻止了直接读写——C 是"既要封装的姿态，又给读写的便利"。
- **D**：用 `double data_[2]` 内部存——为什么？x/y 各占一个字段在内存布局上和数组完全一致，但用数组失去了**字段名义化**的好处。`data_[0]` 不如 `x_` 易读。除非真的需要把 Point2D 当数组用（比如和 OpenGL 接口配合），否则这是**为不存在的需求引入复杂度**。

C++ Core Guidelines C.2: "Use `class` if the class has an invariant; use `struct` if the data members can vary independently"。Point2D 显然属于后者。

但要注意：**这不是说所有"小类"都该是 struct**。如果 Point 需要：
- 维护单位向量约束（norm = 1）→ 需要私有 + 验证 → class
- 提供旋转、距离等操作 → 仍可以是 struct，因为没有不变量

**核心识别点**：
- 无不变量的纯数据 → struct + 公有成员
- 反射式 get/set → Java 习惯传染到 C++，反模式
- 封装 = 隐藏可变状态 + 强制不变量，不是 "强制写代码量"
- 返回引用的 getter 等于 = 公有字段（绕了大圈）

**来源：** 手写题。C++ Core Guidelines C.2 和 C.131: "Avoid trivial getters and setters"。