---
qid: cpp-inh-multi-007
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { int x; };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};

D d;
d.x = 1;   // 这行代码会？
```

A. 编译错误：`x` 不明确
B. 编译正常，修改 `B` 路径的 `x`
C. 编译正常，同时修改两份 `x`
D. 运行时错误
