---
qid: cpp-iv-vtable-005
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, Microsoft]
rubric:
  - 能区分纯虚函数（= 0）与普通虚函数的语法和语义
  - 知道含纯虚函数的类是抽象类，不能实例化
  - 理解纯虚函数可以有实现（定义），派生类可以显式调用
  - 能说出抽象类的设计意图：定义接口契约、强制派生类实现
  - 了解接口类（全纯虚）与部分实现基类的设计差别
---

# 纯虚函数和普通虚函数的区别？抽象类的作用？

### 问题

请说明 C++ 中纯虚函数（pure virtual function）与普通虚函数的区别。什么是抽象类？它的设计意图是什么？

## Explanation

### 语法区别

```cpp
struct Base {
    virtual void ordinary();      // 普通虚函数：有默认实现，派生类可选覆盖
    virtual void pure() = 0;      // 纯虚函数：= 0，强制派生类提供实现
};
```

### 语义差异对比

| 维度 | 普通虚函数 | 纯虚函数 |
|------|-----------|---------|
| 默认实现 | 必须提供 | 不强制（但可以提供） |
| 派生类覆盖 | 可选 | 必须（否则派生类仍是抽象类） |
| 所在类可实例化 | 是 | 否（抽象类） |
| vtable 中的槽 | 存真实函数指针 | 通常存 `__cxa_pure_virtual` 或 nullptr |

### 抽象类

含有至少一个纯虚函数的类称为**抽象类**，不能直接实例化：

```cpp
struct Shape {
    virtual double area() const = 0;    // 纯虚
    virtual void draw() const = 0;      // 纯虚
    virtual ~Shape() = default;
    void describe() { std::cout << "area=" << area() << "\n"; }  // 普通成员函数，允许
};

// Shape s;  // 编译错误：cannot instantiate abstract class

struct Circle : Shape {
    double r;
    Circle(double r) : r(r) {}
    double area() const override { return 3.14159 * r * r; }
    void draw() const override { std::cout << "O\n"; }
};
```

### 纯虚函数可以有实现

这是一个常被忽略的细节：纯虚函数可以提供函数体，派生类可通过显式作用域调用：

```cpp
struct Base {
    virtual void init() = 0;
};
void Base::init() { std::cout << "Base default init\n"; }  // 合法！

struct Derived : Base {
    void init() override {
        Base::init();  // 显式调用基类的纯虚实现
        std::cout << "Derived init\n";
    }
};
```

典型用途：纯虚析构函数（必须提供定义，见 vtable-004）。

### 抽象类的设计意图

1. **定义接口契约**：抽象类声明"派生类必须能做什么"，而不规定"怎么做"。这是依赖倒置原则（DIP）的基础。
2. **防止直接实例化不完整对象**：如 `Shape` 没有具体形状，实例化毫无意义。
3. **文档化设计意图**：阅读者一眼看出这是扩展点。

### 接口类 vs 部分实现基类

```cpp
// 接口类（全纯虚）—— 类似 Java interface
struct ISerializable {
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string&) = 0;
    virtual ~ISerializable() = default;
};

// 部分实现基类（模板方法模式）
struct Logger {
    void log(const std::string& msg) {  // 普通函数，定义骨架
        format(msg);
        write(msg);
    }
    virtual void format(const std::string&) {}           // 可选覆盖
    virtual void write(const std::string& msg) = 0;     // 必须实现
};
```

前者强调"能力接口"，后者提供复用框架并留出扩展点，二者均是抽象类的常见用法。
