---
qid: cpp-inh-multi-013
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};

D d;
d.x = 99;            // 这行代码会？
```

A. 编译错误：`x` 不明确
B. 编译正常，访问唯一的 `A::x`
C. 运行时崩溃
D. 仅修改 `B` 路径的 `x`

## Explanation

正确答案是 B，对应“编译正常，访问唯一的 A::x”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“编译错误：x 不明确”不满足题干要求；C 项“运行时崩溃”不满足题干要求；D 项“仅修改 B 路径的 x”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
