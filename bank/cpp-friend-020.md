---
qid: cpp-friend-020
type: multi
kp: [cpp-friend]
difficulty: easy
answer_key: [A, C, D]
---

下列关于 C++ `friend` 的说法，哪些是正确的？（多选）

A. `friend` 函数在类内声明，但不是类的成员函数，没有 `this` 指针
B. `friend` 关系可以传递：若 A friend B，B friend C，则 A 也是 C 的友元
C. `friend` 声明在 `public`、`private`、`protected` 区域效果完全相同
D. `friend` 关系不能被继承，基类的友元不自动成为派生类的友元
E. 声明 `friend class B` 后，B 中的 `private` 成员也对 A 可见（双向自动生效）
