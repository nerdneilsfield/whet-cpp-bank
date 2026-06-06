---
qid: cpp-inh-multi-014
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A {
    A(int v) { std::cout << "A(" << v << ")"; }
};
struct B : virtual public A {
    B() : A(1) { std::cout << "B"; }
};
struct C : virtual public A {
    C() : A(2) { std::cout << "C"; }
};
struct D : public B, public C {
    D() : A(3), B(), C() { std::cout << "D"; }
};
D d;
```

以下关于虚继承构造规则的说法，正确的是？

A. `A` 由 `B` 的构造函数负责初始化，调用 `A(1)`
B. `A` 由 `C` 的构造函数负责初始化，调用 `A(2)`
C. `A` 由最派生类 `D` 直接负责初始化，调用 `A(3)`；`B` 和 `C` 中对 `A` 的初始化被忽略
D. `A` 被构造三次：`A(1)`、`A(2)`、`A(3)`
