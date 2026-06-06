---
qid: cpp-inh-multi-019
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: D
---

```cpp
struct A { A() { std::cout << "A "; } };
struct B : public A { B() { std::cout << "B "; } };
struct C : public A { C() { std::cout << "C "; } };
struct D : public B, public C { D() { std::cout << "D "; } };
D d;
```

程序输出是？

A. `D A B A C`
B. `A B C D`
C. `A A B C D`
D. `A B A C D`（B 的 A 先构造，再 B，再 C 的 A，再 C，最后 D）
