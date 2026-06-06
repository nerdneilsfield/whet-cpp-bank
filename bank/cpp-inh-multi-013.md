---
qid: cpp-inh-multi-013
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};

D d;
d.x = 99;            // 这行代码会？
```

A. 编译错误：`x` 不明确
B. 编译正常，访问唯一的 `A::x`
C. 运行时崩溃
D. 仅修改 `B` 路径的 `x`
