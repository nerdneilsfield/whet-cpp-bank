---
qid: cpp-real-en-016
type: single
kp: [cpp-functions, cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: easy
answer_key: B
tags: [interview-real, interviewbit]
---
函数重载（function overloading）和函数覆盖（function overriding）的区别是？

A. 两者完全等价，只是名称不同
B. 重载是编译时多态（同一作用域内同名函数不同参数列表），覆盖是运行时多态（派生类重写基类虚函数）
C. 覆盖是编译时多态，重载是运行时多态
D. 重载只能用于全局函数，覆盖只能用于成员函数

---

**解析：**

- **函数重载（Overloading）**：同一作用域内，函数名相同但参数类型/数量不同。编译期根据参数类型选择版本。属于**编译时多态（compile-time polymorphism）**。返回类型不参与重载决议。
- **函数覆盖（Overriding）**：派生类重写基类的 `virtual` 函数。通过基类指针/引用调用时，运行时根据实际对象类型选择版本。属于**运行时多态（runtime polymorphism）**。

```cpp
class Base { virtual void foo(int); };   // virtual
class Derived : public Base { void foo(int) override; };  // overriding
```

**来源：** InterviewBit "C++ Interview Questions" — Overloading vs Overriding

## Explanation

正确答案是 B。
函数重载（Overloading）：同一作用域内，函数名相同但参数类型/数量不同；编译期根据参数类型选择版本。
属于编译时多态（compile-time polymorphism）；返回类型不参与重载决议。
编译期根据参数类型选择版本。
