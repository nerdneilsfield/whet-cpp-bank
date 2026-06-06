---
qid: cpp-inh-multi-005
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

```cpp
struct A { int x; };       // 4 字节
struct B { int y; };       // 4 字节
struct C : public A, public B { int z; };
```

不考虑对齐填充，`sizeof(C)` 最可能是多少？

A. 4
B. 8
C. 12
D. 16

## 解析

正确答案是 C，对应“12”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“4”不满足题干要求；B 项“8”不满足题干要求；D 项“16”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
