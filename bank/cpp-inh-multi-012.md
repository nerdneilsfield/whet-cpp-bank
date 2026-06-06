---
qid: cpp-inh-multi-012
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { int x; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};
```

引入虚继承后，`D` 的对象中 `A` 的子对象有多少份？

A. 1 份（虚继承共享同一份基类子对象）
B. 2 份（分别来自 B 和 C）
C. 0 份（虚继承会省略基类）
D. 取决于编译器实现
