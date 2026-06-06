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

## 解析

本题正确答案是 A, C。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项正确：“Base p = &d;”符合题干要求；B 项错误：“Derived p = &b;”与题干要求或 C++ 规则不符；C 项正确：“Base& r = d;”符合题干要求；D 项错误：“Derived& r = b;”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
