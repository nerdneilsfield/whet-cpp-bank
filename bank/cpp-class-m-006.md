---
qid: cpp-class-m-006
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [A, B, C]
---

关于 C++ 中的 `this` 指针，下列哪些说法**正确**？（选择所有正确项）

A. `this` 是一个指向当前对象的指针，类型为 `ClassName*`（在 `const` 成员函数中为 `const ClassName*`）
B. `this` 指针可以用于在成员函数中区分同名的成员变量与局部变量，例如 `this->x = x;`
C. 成员函数可以通过 `return *this;` 返回当前对象的引用，从而支持链式调用
D. 静态成员函数也有 `this` 指针，但它指向类本身而非某个对象
