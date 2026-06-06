---
qid: cpp-poly-hard-001
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: B
---

考虑多重继承下的对象布局：

```cpp
struct A { virtual void f(); int a; };
struct B { virtual void g(); int b; };
struct D : A, B {
    void f() override;
    void g() override;
    int d;
};

D obj;
A* pa = &obj;
B* pb = &obj;
```

关于 `pa` 与 `pb` 的关系，下列说法正确的是？

A. `pa == pb`，因为它们指向同一个对象
B. `pa` 与 `pb` 数值不同；`B*` 指向 `obj` 内部 `B` 子对象的起始处，需要做指针偏移；同时 `obj` 包含至少两个 vptr，分别对应 A 与 B 子对象
C. 同一对象只有一个 vptr，所以 `pa == pb`，`B::g` 通过虚表第二槽分发
D. 多重继承不支持多态，本代码非法

## Explanation

经典多重非虚继承下，派生类对象在内存中按声明顺序排列基类子对象：`[A 子对象 (vptr_A + a)][B 子对象 (vptr_B + b)][d]`。`A*` 指向对象起始处，`B*` 则指向 `B` 子对象起始处——两者数值不同，编译器在隐式转换 `D*→B*` 时插入偏移调整（pointer adjustment）。各自的虚表用于自身那部分接口的动态分发，因此 `obj` 包含两个 vptr。当 `B*` 上调用 `g()` 时，分发到 `D::g` 后，会通过 thunk 自动调整 `this` 回 `D*`。这也是多重继承产生 vtable thunk 的根源。
