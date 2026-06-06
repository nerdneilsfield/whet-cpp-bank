---
qid: cpp-inh-006
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

基类析构函数未声明为 `virtual`，通过基类指针 `delete` 派生类对象时，会发生什么？

A. 只调用基类析构函数，派生类析构函数不被调用，导致资源泄漏
B. 只调用派生类析构函数
C. 同时调用基类和派生类析构函数
D. 编译报错
