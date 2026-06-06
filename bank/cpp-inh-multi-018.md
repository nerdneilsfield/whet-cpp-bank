---
qid: cpp-inh-multi-018
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [A, C]
---

`std::iostream` 的继承体系是菱形继承的经典例子。下列关于其设计的说法，哪些正确？（多选）

A. `std::istream` 和 `std::ostream` 都虚继承自 `std::ios_base`（经由 `std::basic_ios`）
B. `std::iostream` 使用非虚继承，因此含两份 `ios_base` 子对象
C. 虚继承使 `std::iostream` 对象中只有一份 `basic_ios` 子对象
D. `std::iostream` 不属于菱形继承，`istream` 和 `ostream` 没有共同基类

## 解析

本题正确答案是 A, C。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项正确：“std::istream 和 std::ostream 都虚继承自 std::iosbase（经由 std::basicios）”符合题干要求；B 项错误：“std::iostream 使用非虚继承，因此含两份 iosbase 子对象”与题干要求或 C++ 规则不符；C 项正确：“虚继承使 std::iostream 对象中只有一份 basicios 子对象”符合题干要求；D 项错误：“std::iostream 不属于菱形继承，istream 和 ostream 没有共同基类”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
