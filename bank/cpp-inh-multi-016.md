---
qid: cpp-inh-multi-016
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { int x = 0; void set(int v) { x = v; } };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};

D d;
d.B::set(10);
std::cout << d.B::x << " " << d.C::x;
```

输出结果是？

A. `10 0`（两份 `A` 独立，仅 `B` 路径的被修改）
B. `10 10`（共享同一份 `A`）
C. 编译错误
D. 未定义行为
