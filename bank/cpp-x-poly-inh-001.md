---
qid: cpp-x-poly-inh-001
type: single
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: C
---

下列代码输出是？

```cpp
#include <iostream>

struct Base {
    Base() { init(); }
    virtual void init() { std::cout << "Base::init "; }
};

struct Derived : Base {
    void init() override { std::cout << "Derived::init "; }
};

int main() {
    Derived d;
}
```

A. `Derived::init`
B. `Base::init Derived::init`
C. `Base::init`
D. 未定义行为

---

## Explanation

[class.cdtor]/4 明确规定：**在构造函数和析构函数中，对 `virtual` 函数的调用 **不会发生多态分派**——总是调用 **当前正在构造/析构的类** 所定义的版本（或它能看到的最派生版本）。

执行流程：
1. `Derived d;` 触发 `Derived` 的构造。
2. 先构造基类 `Base`，进入 `Base::Base()`。
3. 在 `Base` 的构造函数中，**`Derived` 子对象尚未构造完成**，此时如果通过 vtable 调用 `Derived::init`，可能访问尚未初始化的 `Derived` 成员，导致 UB。
4. 标准为避免此 UB，规定此时虚函数表 **临时指向 `Base` 的版本**，因此 `init()` 调用 `Base::init`。
5. 输出 `Base::init`，`Derived` 的构造函数体为空，不再输出。

类似规则也适用于析构函数：在 `Derived::~Derived()` 中虚函数调派为 `Derived` 版本；进入 `Base::~Base()` 后，`Derived` 子对象已被销毁，虚函数调派回 `Base` 版本。

避免此陷阱的设计：
1. **不在构造函数里调用虚函数**——把可能依赖派生类行为的初始化挪到 `init()` 函数中，由调用方在对象完全构造后显式调用。
2. 或使用 **二阶段构造**：`auto d = Derived::create();` 工厂方法在 `new Derived` 之后再调用 `init`。
3. Java/C# 等语言在此处行为不同（它们会调派到派生类，但风险是访问未初始化字段），C++ 选择更保守的方式。
