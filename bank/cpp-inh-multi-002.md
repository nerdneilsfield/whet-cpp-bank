---
qid: cpp-inh-multi-002
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

给定以下代码，`C` 的构造函数体执行前，基类构造函数的调用顺序是？

```cpp
struct A { A() { std::cout << "A"; } };
struct B { B() { std::cout << "B"; } };
struct C : public B, public A {
    C() { std::cout << "C"; }
};
C c;
```

A. A → B → C
B. B → A → C
C. C → A → B
D. 顺序未定义，由编译器决定

## 解析

正确答案是 B，对应“B → A → C”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“A → B → C”不满足题干要求；C 项“C → A → B”不满足题干要求；D 项“顺序未定义，由编译器决定”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
