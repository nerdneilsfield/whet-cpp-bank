---
qid: cpp-poly-006
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: C
---

# 为什么通过基类指针 `delete` 派生类对象时，基类析构函数必须声明为 `virtual`？

A. 否则派生类的构造函数不会被调用  
B. 非 `virtual` 析构函数会导致编译错误  
C. 否则只会调用基类析构函数，派生类部分资源无法释放，导致内存泄漏或未定义行为  
D. `virtual` 析构函数会自动调用 `delete[]`
