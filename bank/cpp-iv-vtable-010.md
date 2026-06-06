---
qid: cpp-iv-vtable-010
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Meta, 华为]
rubric:
  - 能准确定义协变返回类型：覆盖函数的返回类型可以是基类返回类型的派生类
  - 知道规则限制：仅适用于指针或引用类型，值类型不允许协变
  - 理解协变返回类型在 vtable 中如何实现（编译器隐式转换，槽存派生返回指针）
  - 能给出工厂方法 / clone 模式中协变返回类型的实际应用示例
  - 知道协变与逆变（contravariance）的区别，及 C++ 只支持协变的原因
---

# 协变返回类型（covariant return type）是什么？

## 问题

什么是协变返回类型（covariant return type）？C++ 对它的规则是什么？它如何在 vtable 层面实现？请给出实际应用场景。

## 参考答案

### 定义

**协变返回类型**：派生类覆盖虚函数时，允许将返回类型从"基类指针/引用"替换为"派生类指针/引用"，且仍被视为合法的覆盖（override），而非新函数。

标准规则（C++98 起）：若基类虚函数返回 `B*`（或 `B&`），派生类可以返回 `D*`（或 `D&`），前提是 `D` 是 `B` 的（公有）派生类，且两者的 cv 限定符兼容。

**仅限指针和引用**，值类型不允许协变（原因：值语义无法多态，且存在切片问题）。

### 基础示例

```cpp
struct Animal {
    virtual Animal* clone() const;      // 基类：返回 Animal*
    virtual ~Animal() = default;
};

struct Dog : Animal {
    Dog* clone() const override;        // 合法协变：返回 Dog*（Dog 是 Animal 的派生）
};

Animal* a = new Dog();
Dog*    d = static_cast<Dog*>(a);
Dog*    copy = d->clone();             // 通过 Dog* 调用，得到 Dog*，无需强转
Animal* copy2 = a->clone();            // 通过 Animal* 调用，得到 Animal*（已隐式转换）
```

如果没有协变，`Dog::clone()` 只能返回 `Animal*`，调用方每次都需要 `static_cast<Dog*>`，既繁琐又类型不安全。

### vtable 层面的实现

协变返回类型在二进制层面的实现方式：

vtable 的函数槽存储的仍然是**具体类型**（`Dog*`）的函数指针。当通过 `Animal*` 调用时，编译器在调用点插入隐式的指针转换（相当于 `(Animal*)result`）。这个转换是编译期完成的，不增加运行时开销（单继承下指针值不变，只是类型重新解释；多重继承时可能需要加偏移）。

```
Animal vtable:
  slot[0] → Animal::clone (返回 Animal*)

Dog vtable:
  slot[0] → Dog::clone_impl (返回 Dog*)
  // 编译器在 Dog vtable 槽中存 Dog::clone 的指针
  // 通过 Animal* 调用时，编译器自动插入 (Animal*) 转换
```

### 实际应用：克隆模式（Prototype Pattern）

协变返回类型在原型模式中最常见：

```cpp
struct Shape {
    virtual Shape* clone() const = 0;
    virtual ~Shape() = default;
};

struct Circle : Shape {
    double radius;
    Circle(double r) : radius(r) {}
    Circle* clone() const override {     // 协变：返回 Circle*
        return new Circle(*this);
    }
};

struct Rectangle : Shape {
    double w, h;
    Rectangle* clone() const override { // 协变：返回 Rectangle*
        return new Rectangle(*this);
    }
};

// 使用时：
Circle c(3.0);
Circle* c2 = c.clone();                 // 直接得到 Circle*，无需强转
Shape*  s  = &c;
Shape*  s2 = s->clone();               // 通过基类指针，得到 Shape*
```

使用智能指针的现代写法（C++11+）：

```cpp
struct Shape {
    virtual std::unique_ptr<Shape> clone() const = 0;
};
struct Circle : Shape {
    // 注意：unique_ptr 不支持协变（模板参数不协变）
    // 必须返回 unique_ptr<Shape>，内部存 Circle
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
};
```

智能指针本身不支持协变（`unique_ptr<Dog>` 不是 `unique_ptr<Animal>` 的派生），因此只能返回基类的 `unique_ptr`。这是协变返回类型的一个重要局限。

### 协变 vs 逆变

| 概念 | 含义 | C++ 支持？ |
|------|------|------------|
| 协变（covariance） | 返回类型可以更具体（派生） | 是（指针/引用） |
| 逆变（contravariance） | 参数类型可以更抽象（基类） | 否 |
| 不变（invariance） | 类型必须完全相同 | 默认 |

C++ 不支持参数类型逆变，原因是重载决议的复杂性——若允许，覆盖判断会与重载判断产生冲突，语义模糊。

### 常见追问

- **为什么值类型不能协变？** 值返回时发生对象切片（object slicing），`Animal clone()` 返回的是 `Animal` 的副本，不是 `Dog`；允许协变值类型会掩盖这个问题。
- **Java/C# 支持协变返回类型吗？** Java 5+ 支持，C# 9+ 支持（仅引用类型，与 C++ 规则类似）。
