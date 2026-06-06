---
qid: cpp-inh-multi-001
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

下列哪种写法正确声明了一个同时公有继承 `A` 和 `B` 的类 `C`？

A. `class C : public A; public B {};`
B. `class C extends A, B {};`
C. `class C : public A, public B {};`
D. `class C : public A && public B {};`

## 解析

正确答案是 C，对应“class C : public A, public B {};”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“class C : public A; public B {};”不满足题干要求；B 项“class C extends A, B {};”不满足题干要求；D 项“class C : public A && public B {};”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
