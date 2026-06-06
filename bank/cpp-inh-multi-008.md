---
qid: cpp-inh-multi-008
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x = 0; };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};

D d;
d.B::x = 42;
std::cout << d.C::x;  // 输出什么？
```

A. 42
B. 编译错误
C. 0（两份 `x` 独立，`d.C::x` 未被修改）
D. 未定义行为

## Explanation

正确答案是 C，对应“0（两份 x 独立，d.C::x 未被修改）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“42”不满足题干要求；B 项“编译错误”不满足题干要求；D 项“未定义行为”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
