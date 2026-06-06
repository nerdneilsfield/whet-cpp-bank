---
qid: cpp-inh-multi-006
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

```cpp
struct A { int x; };
struct B : public A {};
struct C : public A {};
struct D : public B, public C {};
```

关于此菱形继承，下列说法正确的是？

A. `D` 中只含一份 `A` 的数据成员
B. `D` 中含两份 `A` 的数据成员（分别来自 `B` 和 `C`）
C. 这段代码无法通过编译
D. `A` 的成员会被 `D` 忽略

## 解析

正确答案是 B，对应“D 中含两份 A 的数据成员（分别来自 B 和 C）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“D 中只含一份 A 的数据成员”不满足题干要求；C 项“这段代码无法通过编译”不满足题干要求；D 项“A 的成员会被 D 忽略”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
