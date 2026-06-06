---
qid: cpp-inh-multi-020
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { virtual ~A() {} };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};

D d;
B* pb = &d;
A* pa = dynamic_cast<A*>(pb);  // 这行代码会？
```

A. 编译错误：`dynamic_cast` 不支持多重继承
B. 编译通过，但因菱形继承存在两份 `A` 子对象，`dynamic_cast<A*>(pb)` 结果明确，指向 `B` 路径的 `A`
C. 总是返回 `nullptr`
D. 等价于 `static_cast<A*>(pb)`，无运行时开销
