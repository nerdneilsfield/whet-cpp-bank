---
qid: cpp-inh-018
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [B, D]
---

以 `protected` 方式继承基类时，下列说法哪些正确？

A. 基类 `public` 成员在派生类中仍为 `public`
B. 基类 `public` 成员在派生类中变为 `protected`
C. 基类 `protected` 成员在派生类中变为 `private`
D. 基类 `protected` 成员在派生类中仍为 `protected`

## Explanation

本题正确答案是 B, D。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项错误：“基类 public 成员在派生类中仍为 public”与题干要求或 C++ 规则不符；B 项正确：“基类 public 成员在派生类中变为 protected”符合题干要求；C 项错误：“基类 protected 成员在派生类中变为 private”与题干要求或 C++ 规则不符；D 项正确：“基类 protected 成员在派生类中仍为 protected”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
