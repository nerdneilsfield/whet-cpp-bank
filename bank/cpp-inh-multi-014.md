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

## Explanation

正确答案是 C，对应“A 由最派生类 D 直接负责初始化，调用 A(3)；B 和 C 中对 A 的初始化被忽略”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“A 由 B 的构造函数负责初始化，调用 A(1)”不满足题干要求；B 项“A 由 C 的构造函数负责初始化，调用 A(2)”不满足题干要求；D 项“A 被构造三次：A(1)、A(2)、A(3)”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
