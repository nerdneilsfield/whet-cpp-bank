---
qid: cpp-inh-003
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

以 `private` 方式继承基类时，基类的 `public` 成员在派生类中变为什么访问级别？

A. `public`
B. `private`
C. `protected`
D. 不变，仍为 `public`

## 解析

正确答案是 B，对应“private”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：A 项“public”不满足题干要求；C 项“protected”不满足题干要求；D 项“不变，仍为 public”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
