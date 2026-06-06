---
qid: cpp-taste-class-018
type: single
kp: [cpp-classes, cpp-special-members, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: hard
answer_key: A
tags: [code-taste, best-practice, virtual-dtor]
---
设计一个**会被继承且多态使用**的基类 `Animal`。哪个版本品味最好？

```cpp
// A
class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() const = 0;
};
class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof"; }
};
// std::unique_ptr<Animal> a = std::make_unique<Dog>();

// B
class Animal {
public:
    ~Animal() = default;
    virtual void speak() const = 0;
};
class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof"; }
};

// C
class Animal {
protected:
    ~Animal() = default;
public:
    virtual void speak() const = 0;
};
class Dog : public Animal {
public:
    ~Dog() = default;
    void speak() const override { std::cout << "Woof"; }
};

// D
class Animal {
public:
    virtual ~Animal() {}
    virtual void speak() = 0;
};
class Dog : public Animal {
public:
    ~Dog() override {}
    void speak() override { std::cout << "Woof"; }
};
```

A. A — virtual ~Animal() = default，支持多态 delete，规范且零写法
B. B — 非 virtual dtor 也能用，反正用 unique_ptr<Dog> 不会用基类指针
C. C — protected dtor 阻止外部对基类指针 delete，防误用
D. D — virtual dtor + 空 body，所有 const 都去掉以保留写入能力

---

**解析：**

选 A。这道题考的是 **多态基类必须 virtual dtor + 用 `= default` 是惯例**。

逐一品味：

- **A**：标准模板。
  - `virtual ~Animal() = default` 让基类正确支持多态 delete：`delete static_cast<Animal*>(dog)` 调用 Dog::~Dog() 然后 Animal::~Animal()
  - `= default` 比空 body 更明确——告诉读者"析构没有特殊逻辑，仅触发虚分派"
  - 纯虚 `speak()` 强制派生类实现
  - `const` 表达"speak 不修改状态"——多态接口应尽量 const
  
  Dog 用 override 显式表达意图，编译器检查签名匹配。
- **B**：**致命错误**。`~Animal() = default` 非 virtual。当用户 `std::unique_ptr<Animal> a = std::make_unique<Dog>(); a.reset();`——只调用 `Animal::~Animal()`，**不调用 Dog::~Dog()**。Dog 持有的资源（如 vector、unique_ptr）不会被释放——**资源泄漏 + UB**（标准明确：通过基类指针 delete 派生类对象需 virtual dtor）。
- **C**：`protected` dtor 是一种特殊设计——禁止通过基类指针 delete。**但 C 没声明 virtual**——所以即使有人在 derived class 中用基类指针 delete（通过友元），也是 UB。protected dtor 的正确用法是 **`protected: virtual ~Animal() = default;`** 或者 `protected: ~Animal() = default;` （前者允许派生类间接析构，但禁止外部 delete）。C 的组合不安全且不标准。
- **D**：
  - 移除了 `const`——`virtual void speak()` 让 const 对象 `const Dog& d` 无法调用 `speak()`，限制接口
  - `virtual ~Animal() {}` 用空 body 而不是 `= default`——功能等价但 `= default` 表意更准
  - 派生类的 `~Dog() override {}` 是冗余的（编译器会生成），写空 body 没用
  
  全是噪音。

A 的简洁是 hard-won：每行都精准对应一个语义，没有冗余、没有遗漏、没有未来的坑。这是"对 modern C++ 基类的肌肉记忆"。

**核心识别点**：
- 多态基类 → 必须 virtual dtor，否则通过基类指针 delete 是 UB
- `= default` 比空 body 更表达意图
- `override` 在派生类强制签名检查
- const-correctness 在多态接口中应贯彻
- `protected` dtor 是特殊用法，需配合 virtual 才安全

**来源：** 手写题。C++ Core Guidelines C.35: "A base class destructor should be either public and virtual, or protected and non-virtual"；Scott Meyers Item 7。

## Explanation

正确答案是 A。protected dtor 的正确用法是 `protected: virtual ~Animal() = default;` 或者 `protected: ~Animal() = default;` （前者允许派生类间接析构，但禁止外部 delete）。
Dog 持有的资源（如 vector、unique_ptr）不会被释放——资源泄漏 + UB（标准明确：通过基类指针 delete 派生类对象需 virtual dtor）。
常见误区是只看表面语法或局部运行结果，忽略标准规则和工程边界条件。
