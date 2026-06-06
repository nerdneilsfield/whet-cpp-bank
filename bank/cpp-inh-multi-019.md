---
qid: cpp-inh-multi-019
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: D
---

```cpp
struct A { A() { std::cout << "A "; } };
struct B : public A { B() { std::cout << "B "; } };
struct C : public A { C() { std::cout << "C "; } };
struct D : public B, public C { D() { std::cout << "D "; } };
D d;
```

程序输出是？

A. `D A B A C`
B. `A B C D`
C. `A A B C D`
D. `A B A C D`（B 的 A 先构造，再 B，再 C 的 A，再 C，最后 D）

## 解析

正确答案是 D，对应“A B A C D（B 的 A 先构造，再 B，再 C 的 A，再 C，最后 D）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“D A B A C”不满足题干要求；B 项“A B C D”不满足题干要求；C 项“A A B C D”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
