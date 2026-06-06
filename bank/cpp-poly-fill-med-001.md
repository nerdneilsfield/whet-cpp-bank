---
qid: cpp-poly-fill-med-001
type: fill
kp: [cpp-polymorphism]
difficulty: medium
answer_key: "= 0"
---
纯虚函数声明语法 `virtual void f() ___`。

---

**解析：**

在虚函数声明的末尾加上 `= 0` 使其成为纯虚函数（pure virtual function）。含有纯虚函数的类称为抽象类，不能直接实例化。派生类必须实现所有纯虚函数才能成为具体类。这一机制实现了 C++ 的接口抽象（interface-like design）。