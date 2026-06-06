---
qid: cpp-inh-med-002
type: single
kp: [cpp-inheritance]
difficulty: medium
answer_key: B
---

下列代码使用了虚继承中的"支配规则"（dominance），`d.f()` 输出什么？

```cpp
struct A         { void f() { std::cout << "A"; } };
struct B : virtual A { void f() { std::cout << "B"; } };
struct C : virtual A {};
struct D : B, C  {};

D d;
d.f();
```

A. 编译错误：`f` 名称在 `B` 和 `A`（经由 `C`）中都可见，存在歧义
B. 输出 `B`
C. 输出 `A`
D. 编译错误：虚继承下不能调用基类同名非虚函数

---

**解析：**

非虚继承下，`d.f()` 通常会因为 `B::f` 和 `A::f`（经由 `C`）在派生类中产生两个独立的名字而歧义。但 `A` 是**虚基类**：`B`、`C` 共享同一个 `A` 子对象。

支配规则（[class.member.lookup]）规定：名字查找时，如果一条路径上的声明"支配"另一条路径上的声明（即派生类同名成员覆盖虚基类中的同名成员），歧义就被解除。这里 `B::f` 支配 `A::f`，所以 `d.f()` 无歧义地调用 `B::f`，输出 `B`。注意如果 `A` 不是虚基类，这段代码就会编译失败。
