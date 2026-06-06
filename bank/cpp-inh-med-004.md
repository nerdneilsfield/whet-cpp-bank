---
qid: cpp-inh-med-004
type: single
kp: [cpp-inheritance]
difficulty: medium
answer_key: C
---

下列继承关系中，构造 `D d;` 时构造函数调用顺序是？

```cpp
struct A { A() { std::cout << "A"; } };
struct B : virtual A { B() { std::cout << "B"; } };
struct C : virtual A { C() { std::cout << "C"; } };
struct D : B, C       { D() { std::cout << "D"; } };
```

A. `A B A C D`
B. `B A C A D`
C. `A B C D`
D. `B C A D`

---

**解析：**

C++ 构造顺序规则（[class.base.init]）：先**所有虚基类**（按继承图深度优先、从左到右的顺序，但每个虚基类只构造一次），再非虚直接基类（按声明顺序），最后派生类自身。

这里 `A` 是 `B` 和 `C` 共享的虚基类，整个 `D` 对象里只有一个 `A` 子对象，由最派生类 `D` 触发，最先构造，输出 `A`。然后按 `D : B, C` 的声明顺序构造非虚直接基类 `B`、`C`，输出 `B C`。最后是 `D` 自己，输出 `D`。

析构顺序严格相反：`~D ~C ~B ~A`。把 `virtual` 去掉后，`A` 会在 `B` 之前、`C` 之前各构造一次，输出变成 `A B A C D`，对应选项 A——这就是引入虚继承的目的。

## Explanation

正确答案是 C，对应“A B C D”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“A B A C D”不满足题干要求；B 项“B A C A D”不满足题干要求；D 项“B C A D”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
