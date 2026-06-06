---
qid: cpp-inh-multi-017
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x = 7; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};

D d;
d.x = 42;
std::cout << d.B::x << " " << d.C::x << " " << d.x;
```

输出结果是？

A. `7 7 42`
B. `42 7 42`
C. `42 42 42`（虚继承共享唯一 `A`，三种路径指向同一 `x`）
D. 编译错误

## Explanation

正确答案是 C，对应“42 42 42（虚继承共享唯一 A，三种路径指向同一 x）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“7 7 42”不满足题干要求；B 项“42 7 42”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
