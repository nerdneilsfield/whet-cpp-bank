---
qid: cpp-inh-multi-010
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

下列继承关系中，哪个构成菱形继承（diamond inheritance）？

A.
```cpp
struct A {};
struct B : public A {};
struct C : public B {};
```

B.
```cpp
struct A {};
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};
```

C.
```cpp
struct A {};
struct B {};
struct C : public A, public B {};
```

D.
```cpp
struct A {};
struct B : public A {};
struct C : public A {};
```
