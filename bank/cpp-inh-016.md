---
qid: cpp-inh-016
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [A, C]
---

以下哪些赋值操作合法（满足 `is-a` 关系）？

```cpp
struct Base {};
struct Derived : public Base {};

Derived d;
Base b;
```

A. `Base* p = &d;`
B. `Derived* p = &b;`
C. `Base& r = d;`
D. `Derived& r = b;`
