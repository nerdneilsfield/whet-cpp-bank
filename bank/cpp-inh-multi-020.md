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

## 解析

正确答案是 B，对应“编译通过，但因菱形继承存在两份 A 子对象，dynamiccast<A>(pb) 结果明确，指向 B 路径的 A”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“编译错误：dynamiccast 不支持多重继承”不满足题干要求；C 项“总是返回 nullptr”不满足题干要求；D 项“等价于 staticcast<A>(pb)，无运行时开销”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
