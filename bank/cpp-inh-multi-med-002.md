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