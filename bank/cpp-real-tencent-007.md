---
qid: cpp-real-tencent-007
type: single
kp: [cpp-polymorphism, cpp-special-members]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: D
tags: [interview-real, tencent]
---
```cpp
class Base {
public:
    Base()  { /* 此时是 Base，调用 init() 应该走 Base 版本 */ init(); }
    virtual void init() { std::cout << "Base init\n"; }
    ~Base() { /* 析构时也是 Base */ }
};
class Derived : public Base {
public:
    Derived() : Base() {}
    void init() override { std::cout << "Derived init\n"; }
};
```
关于"构造函数为什么不能是虚函数"和"析构函数为什么应该是虚函数"，以下说法**不正确**的是：

A. 构造函数不能虚：构造期间虚表指针（vptr）还未指向当前类型的 vtable，无法实现多态分发
B. 构造函数中调用虚函数，调用的是当前类的版本，不是派生类版本（vptr 在分阶段构造时逐步设置）
C. 析构函数应该虚：当基类指针 delete 派生对象时，若析构非虚则只调用 Base 的析构，派生类资源泄漏
D. 析构函数若是虚函数会增加 8 字节的 vptr 开销，所以应避免在性能敏感场景使用虚析构

---

**解析：**

选 D（说法错误的项）。

**为什么构造函数不能是虚函数？**
- 虚函数靠 vptr → vtable 实现动态分发
- 对象构造时，**vptr 还没设置**（构造过程才填充 vptr）
- 派生对象构造时：先调用 Base()，**此时 vptr 指向 Base 的 vtable**，故 Base 构造函数中调虚函数走的是 Base 版本；接着 Derived 构造体执行前才把 vptr 重新指向 Derived 的 vtable

**为什么析构函数应该是虚函数（基类）？**
```cpp
Base* p = new Derived;
delete p;  // 如果 ~Base 非虚 → 只调 ~Base，Derived 的资源泄漏
```

**为什么 D 错？** vptr 只取决于类是否有虚函数。如果一个类已经有任意虚函数（比如成员函数），那么它**已经有 vptr 了**，再加虚析构不会额外增加大小。如果一个类是"final"且确定不会被继承，可以不加 vptr，但只要有继承可能就应该加。

实践规则：**只要类可能作为基类被继承，析构函数就应该是 virtual**（或者将类标记为 final）。

**来源：** 腾讯 / huihut/interview C++ 经典考题

## Explanation

正确答案是 D。
选 D（说法错误的项）。
*为什么构造函数不能是虚函数？
虚函数靠 vptr → vtable 实现动态分发 对象构造时，vptr 还没设置（构造过程才填充 vptr） 派生对象构造时：先调用 Base()，此时 vptr 指向 Base 的 vtable，故 Base 构造函数中调虚函数走的是 Base 版本；接着 Derived 构造体执行前才把 vptr 重新指向 Derived 的 vtable *为什么析构函数应该是虚函数（基类）？
