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

## 解析

正确答案是 B，对应“cpp struct A {}; struct B : public A {}; struct C : public A {}; struct D : public B, public C {}; ”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“cpp struct A {}; struct B : public A {}; struct C : public B {}; ”不满足题干要求；C 项“cpp struct A {}; struct B {}; struct C : public A, public B {}; ”不满足题干要求；D 项“cpp struct A {}; struct B : public A {}; struct C : public A {}; ”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
