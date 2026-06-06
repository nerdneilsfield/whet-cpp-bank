---
qid: cpp-real-en-027
type: single
kp: [cpp-polymorphism, cpp-special-members]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: B
tags: [interview-real, geeksforgeeks]
---
在 C++ 构造函数中能否调用虚函数？行为上有什么特殊之处？

A. 构造函数中不能调用任何成员函数
B. 构造函数中可以调用虚函数，但不会动态绑定——会调用当前类（而非最派生类）的版本
C. 构造函数中调用虚函数与正常调用一样，完全动态绑定
D. 构造函数中调用虚函数会导致编译错误

---

**解析：**

在构造函数的执行过程中，对象处于**部分构造**状态。当执行基类构造函数时，派生类部分还未初始化，此时 vptr (虚表指针) 指向的是**当前正在构造的类的 vtable**，而非最派生类的。

因此，在构造函数（或析构函数）中调用虚函数时，调用的是当前类（或已构造完毕的最近派生类）的版本，而非最终派生类的版本——这叫做**静态绑定**在这个场景下生效。

```cpp
class Base {
public:
    Base() { foo(); }   // 调用 Base::foo
    virtual void foo() { std::cout << "Base\n"; }
};
class Derived : public Base {
public:
    Derived() { foo(); }  // 调用 Derived::foo
    void foo() override { std::cout << "Derived\n"; }
};
// Derived d;  // 输出: Base 然后 Derived
```

**来源：** GeeksforGeeks "Virtual Function in Constructor"

## Explanation

正确答案是 B。
在构造函数的执行过程中，对象处于部分构造状态。当执行基类构造函数时，派生类部分还未初始化，此时 vptr (虚表指针) 指向的是当前正在构造的类的 vtable，而非最派生类的。
因此，在构造函数（或析构函数）中调用虚函数时，调用的是当前类（或已构造完毕的最近派生类）的版本，而非最终派生类的版本——这叫做静态绑定在这个场景下生效。
