---
qid: cpp-inh-med-005
type: single
kp: [cpp-inheritance]
difficulty: medium
answer_key: D
---

下列代码哪一行能让 `d.f(3.14)` 合法编译并调用 `Base::f(double)`？

```cpp
struct Base    { void f(int){} void f(double){} };
struct Derived : Base {
    void f(int){}            // 隐藏了 Base 中所有名为 f 的重载
    // <— 这里加什么？
};

Derived d;
d.f(3.14);   // 期望调用 Base::f(double)
```

A. `virtual void f(double) = 0;`
B. `void f(double) override;`
C. `Base::f(3.14);`
D. `using Base::f;`

---

**解析：**

C++ 名称查找规则：派生类中只要声明了任何一个名为 `f` 的成员，就会**隐藏**（hide）基类中所有同名成员——无论参数列表是否匹配。所以 `Derived::f(int)` 把 `Base::f(double)` 一并遮住了，`d.f(3.14)` 会因为 `Derived::f(int)` 的 `double→int` 转换被选中（窄化警告），而非调用 `Base::f(double)`。

`using Base::f;`（D）把 `Base` 中所有名为 `f` 的重载引入到 `Derived` 作用域，与 `Derived::f(int)` 一起构成重载集，`d.f(3.14)` 才能正确解析到 `Base::f(double)`。

B 的 `override` 只能用于虚函数，而本题 `f` 非虚，写 `override` 会编译错误；A 把函数变纯虚还破坏了类的可实例化性；C 的写法不是声明，无法放在类体内当成员。`using` 与 `override` 解决的是完全不同的问题：前者是名字查找/重载可见性，后者是虚函数重写校验。
