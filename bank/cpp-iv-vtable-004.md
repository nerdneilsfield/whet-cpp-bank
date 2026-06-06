---
qid: cpp-iv-vtable-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, Meta, Amazon]
rubric:
  - 能说清楚不加 virtual 析构时，通过基类指针 delete 派生类对象是 UB
  - 知道原因：非虚析构静态绑定，只调用基类析构，派生类资源泄漏
  - 加 virtual 后析构走虚函数分派，先调用派生类析构再调基类析构
  - 知道纯虚析构的写法和使用场景（抽象基类但不想留纯虚成员函数）
  - 有 RAII/智能指针场景下的补充说明可加分
---

# 为什么基类析构函数要声明为 virtual？不加会怎样？

### 问题

在 C++ 中，为什么建议（或要求）将基类的析构函数声明为 `virtual`？如果不加 `virtual`，会发生什么？

## Explanation

### 不加 virtual 时的问题

若基类析构函数不是虚函数，通过基类指针 `delete` 一个派生类对象时，析构函数的调用是**静态绑定**的——编译器在编译期就决定调用 `Base::~Base()`，**永远不会**调用 `Derived::~Derived()`。

```cpp
struct Base {
    ~Base() { std::cout << "Base dtor\n"; }  // 非虚
};
struct Derived : Base {
    int* data;
    Derived() : data(new int[100]) {}
    ~Derived() { delete[] data; std::cout << "Derived dtor\n"; }
};

Base* p = new Derived();
delete p;  // !! UB：只调用 Base::~Base()，data 泄漏，Derived::~Derived() 从未执行
```

C++ 标准明确：通过基类指针删除派生类对象，若基类析构非虚，行为未定义（undefined behavior）。

### 加 virtual 后的正确行为

```cpp
struct Base {
    virtual ~Base() { std::cout << "Base dtor\n"; }
};
struct Derived : Base {
    int* data;
    Derived() : data(new int[100]) {}
    ~Derived() override { delete[] data; std::cout << "Derived dtor\n"; }
};

Base* p = new Derived();
delete p;
// 输出：
// Derived dtor   ← 先调派生类
// Base dtor      ← 再调基类（编译器自动调用）
```

`virtual ~Base()` 使析构走 vtable 分派：运行时找到 `Derived::~Derived()`，执行完后编译器自动调用 `Base::~Base()`，析构链完整。

### 纯虚析构

想让基类成为抽象类但又不想强制子类实现某个纯虚函数时，可以将析构函数声明为纯虚：

```cpp
struct AbstractBase {
    virtual ~AbstractBase() = 0;  // 纯虚析构
};
AbstractBase::~AbstractBase() {}  // 必须提供定义！否则链接错误
```

注意：纯虚析构必须提供函数体，因为派生类析构链最终一定会调到它。

### 例外情况

不是所有基类都需要 virtual 析构：
- **不打算被多态使用**的基类（如 mixin、CRTP 基类，始终通过派生类指针操作）可以不加，以节省 vtable 开销。
- `std::unique_ptr<Base>` 的 `Deleter` 可以定制，但默认用 `delete`，所以上述规则同样适用。
- 若使用 `shared_ptr<Base>`，`shared_ptr` 在构造时捕获了具体类型的删除器，即使基类析构非虚也能正确析构——但这是例外，依赖此行为不健壮。

### 一句话总结

> 只要一个类会被多态使用（通过基类指针/引用管理派生类对象），就必须将析构函数声明为 `virtual`，否则资源泄漏且行为未定义。
