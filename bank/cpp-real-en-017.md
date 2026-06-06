---
qid: cpp-real-en-017
type: single
kp: [cpp-polymorphism, cpp-special-members]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: C
tags: [interview-real, interviewbit]
---
为什么需要将基类的析构函数声明为 `virtual`？如果不声明会怎样？

A. 如果基类析构函数不是虚函数，派生类将无法定义自己的析构函数
B. 虚析构函数提供更快的析构速度
C. 通过基类指针 `delete` 派生类对象时，如果基类析构不是虚函数，只会调用基类析构函数，不调用派生类析构函数，导致资源泄漏
D. 虚析构函数自动释放所有成员变量的内存

---

**解析：**

通过基类指针 `delete` 派生类对象时：
- **如果基类析构函数是 `virtual`**：运行时动态绑定，先调用派生类析构函数，再调用基类析构函数，正确释放所有资源。
- **如果基类析构函数不是 `virtual`**：编译期静态绑定，只会调用基类析构函数，派生类的析构函数不执行，导致派生类中分配的资源泄漏（如 `new` 分配的内存、打开的文件句柄等）。

**最佳实践**：如果类被设计为基类（有虚函数），析构函数必须声明为 `virtual`。否则可以非虚。

**来源：** InterviewBit "C++ Interview Questions" — Virtual Destructor