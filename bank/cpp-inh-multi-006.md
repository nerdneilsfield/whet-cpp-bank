---
qid: cpp-inh-multi-006
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};
```

关于此菱形继承，下列说法正确的是？

A. `D` 中只含一份 `A` 的数据成员
B. `D` 中含两份 `A` 的数据成员（分别来自 `B` 和 `C`）
C. 这段代码无法通过编译
D. `A` 的成员会被 `D` 忽略
