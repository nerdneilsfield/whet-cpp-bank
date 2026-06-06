---
qid: cpp-poly-multi-hard-001
type: multi
kp: [cpp-polymorphism]
difficulty: hard
answer_key: [A, B, D]
---
关于在构造函数和析构函数中调用虚函数，以下说法正确的是哪些？

```cpp
struct Base {
    Base()  { f(); }     // (1)
    virtual ~Base() { f(); }   // (2)
    virtual void f() { std::cout << "Base\n"; }
};
struct Derived : Base {
    void f() override { std::cout << "Derived\n"; }
};
Derived d;   // 输出什么？
```

A. (1) 在 `Base` 构造函数中调用 `f()` 会调用 `Base::f()`——因为构造期间对象的动态类型仍是 `Base`，vtable 指针尚未指向 `Derived`。
B. (2) 在 `~Base()` 中调用 `f()` 也会调用 `Base::f()`——析构过程中派生部分先销毁，对象类型逐步"退化"为 `Base`。
C. 通过显式限定 `Base::f()` 或 `this->Base::f()` 可以在构造时调用派生类版本。
D. 构造函数中调用纯虚函数（pure virtual）是未定义行为，典型表现为运行时报告 "pure virtual method called" 并终止程序。

---

**解析：**

A 正确：派生类构造时先构造基类子对象，基类构造期间 vptr 已设置为 `Base` 的 vtable，因此 `f()` 解析到 `Base::f()`；这是 Effective C++ Item 9 的经典告诫。
B 正确：析构顺序与构造相反，进入 `~Base` 时 `Derived` 部分已销毁，vptr 已指回 `Base`，调用解析到 `Base::f()`，输出 `Base`。
C 错误：显式 `Base::f()` 是"显式限定调用"，根本不是动态分派；选项描述"调用派生类版本"完全错误——构造期间无法调用 `Derived::f()`，这是语言机制决定的。
D 正确：若 `f` 是纯虚函数，构造期间通过虚分派到达"未实现"的 `Base::f` 表项会调用 `__cxa_pure_virtual`，运行时报错终止，是经典 UB 表现。

## Explanation

A、B、D 正确：基类构造函数和析构函数中调用虚函数都会解析到当前构造/析构阶段的类版本，而不是派生类版本。显式限定 `Base::f()` 更是静态调用，不可能调用派生实现。常见误区是在构造函数里依赖虚函数完成派生初始化；若目标是纯虚函数，还可能直接触发未定义行为。
