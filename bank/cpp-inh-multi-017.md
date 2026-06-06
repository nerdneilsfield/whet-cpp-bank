---
qid: cpp-inh-multi-017
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x = 7; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};

D d;
d.x = 42;
std::cout << d.B::x << " " << d.C::x << " " << d.x;
```

输出结果是？

A. `7 7 42`
B. `42 7 42`
C. `42 42 42`（虚继承共享唯一 `A`，三种路径指向同一 `x`）
D. 编译错误
