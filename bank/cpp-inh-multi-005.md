---
qid: cpp-inh-multi-005
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x; };       // 4 字节
struct B { int y; };       // 4 字节
struct C : public A, public B { int z; };
```

不考虑对齐填充，`sizeof(C)` 最可能是多少？

A. 4
B. 8
C. 12
D. 16
