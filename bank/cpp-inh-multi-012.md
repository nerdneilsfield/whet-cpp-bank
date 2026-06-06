---
qid: cpp-inh-multi-012
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { int x; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {};
```

引入虚继承后，`D` 的对象中 `A` 的子对象有多少份？

A. 1 份（虚继承共享同一份基类子对象）
B. 2 份（分别来自 B 和 C）
C. 0 份（虚继承会省略基类）
D. 取决于编译器实现

## 解析

正确答案是 A，对应“1 份（虚继承共享同一份基类子对象）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：B 项“2 份（分别来自 B 和 C）”不满足题干要求；C 项“0 份（虚继承会省略基类）”不满足题干要求；D 项“取决于编译器实现”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
