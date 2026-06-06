---
qid: cpp-inh-001
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

C++ 中，声明单继承的正确语法是哪一项？

A. `class Derived(Base) {}`
B. `class Derived : public Base {}`
C. `class Derived extends Base {}`
D. `class Derived -> Base {}`

## Explanation

正确答案是 B，对应“class Derived : public Base {}”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“class Derived(Base) {}”不满足题干要求；C 项“class Derived extends Base {}”不满足题干要求；D 项“class Derived -> Base {}”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
