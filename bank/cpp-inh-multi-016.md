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

## 解析

正确答案是 A，对应“10 0（两份 A 独立，仅 B 路径的被修改）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：B 项“10 10（共享同一份 A）”不满足题干要求；C 项“编译错误”不满足题干要求；D 项“未定义行为”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
