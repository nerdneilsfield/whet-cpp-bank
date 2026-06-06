---
qid: cpp-inh-multi-002
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

给定以下代码，`C` 的构造函数体执行前，基类构造函数的调用顺序是？

```cpp
struct A { A() { std::cout << "A"; } };
struct B { B() { std::cout << "B"; } };
struct C : public B, public A {
    C() { std::cout << "C"; }
};
C c;
```

A. A → B → C
B. B → A → C
C. C → A → B
D. 顺序未定义，由编译器决定
