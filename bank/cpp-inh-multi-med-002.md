---
qid: cpp-inh-multi-med-002
type: multi
kp: [cpp-inheritance]
difficulty: medium
answer_key: [A, B, C]
---
关于对象切片（object slicing），**哪些场景会发生切片**？（多选）

A. 将 `Derived` 对象按值赋给 `Base` 类型变量。
B. 函数按值（by value）接收 `Base` 参数，传入 `Derived` 对象。
C. `std::vector<Base>` 中 `push_back` 一个 `Derived` 对象。
D. 通过 `Base&` 引用绑定到 `Derived` 对象后调用虚函数。

---

**解析：**

A 正确：按值赋值时只拷贝 Base 子对象，派生部分被切掉。
B 正确：值传参等同于拷贝构造 Base 对象，发生切片。
C 正确：容器存储 `Base` 值类型，元素只能存 Base 部分，发生切片。
D 错误：引用/指针不切片，虚函数能正常多态分派。

## 解析

本题正确答案是 A, B, C。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项正确：“将 Derived 对象按值赋给 Base 类型变量。”符合题干要求；B 项正确：“函数按值（by value）接收 Base 参数，传入 Derived 对象。”符合题干要求；C 项正确：“std::vector<Base> 中 pushback 一个 Derived 对象。”符合题干要求；D 项错误：“通过 Base& 引用绑定到 Derived 对象后调用虚函数。”与题干要求或 C++ 规则不符。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
