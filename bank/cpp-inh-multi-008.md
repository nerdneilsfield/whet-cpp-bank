---
qid: cpp-inh-multi-008
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x = 0; };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};

D d;
d.B::x = 42;
std::cout << d.C::x;  // 输出什么？
```

A. 42
B. 编译错误
C. 0（两份 `x` 独立，`d.C::x` 未被修改）
D. 未定义行为
