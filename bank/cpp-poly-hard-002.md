---
qid: cpp-poly-hard-002
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: D
---

以下代码运行行为如何？

```cpp
struct Base {
    virtual void cleanup() = 0;
    ~Base() { cleanup(); }
};

struct Derived : Base {
    void cleanup() override { /* ... */ }
};

Derived d;
```

A. 正常运行，调用 `Derived::cleanup`
B. 调用 `Base::cleanup`，但因为它是纯虚函数所以是空操作
C. 编译错误，纯虚函数不能在析构中调用
D. 析构 `d` 时，先调用 `Derived::~Derived()`，然后 `Base::~Base()` 中 `this` 被视为 `Base` 类型，此时调用纯虚函数 `cleanup()` 是未定义行为（通常触发 `__cxa_pure_virtual` 终止）

## Explanation

在构造/析构函数中调用虚函数时，**vptr 被设置为当前正在构造/析构的那一层**（基类层级）。`Derived` 析构完成后进入 `Base::~Base()`，此时 `Derived` 部分已被析构，`this` 在动态上"是 `Base`"——调用 `cleanup()` 不会派发到 `Derived::cleanup`，而是查找 `Base` 自身的 vtable 槽。由于 `cleanup` 是纯虚（在 `Base` 中没有定义），该 vtable 槽指向编译器提供的占位符（GCC 中为 `__cxa_pure_virtual`），调用即终止程序——标准上属于未定义行为（更精确地说："the effect of a call to a pure virtual function during construction or destruction is undefined"）。要避免，应避免在 ctor/dtor 中调用虚函数，或为纯虚函数提供定义。
