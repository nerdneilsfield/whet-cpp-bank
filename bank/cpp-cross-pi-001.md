---
qid: cpp-cross-pi-001
type: single
kp: [cpp-polymorphism, cpp-inheritance]
difficulty: easy
answer_key: D
---

以下代码的输出是什么？

```cpp
#include <iostream>

struct A {
    virtual void speak() { std::cout << "A\n"; }
};

struct B : A {
    void speak() override { std::cout << "B\n"; }
};

struct C : B {
    void speak() override { std::cout << "C\n"; }
};

int main() {
    A* p = new C();
    p->speak();
    delete p;
    return 0;
}
```

A. A  
B. B  
C. 编译错误  
D. C

<!--
三层继承链 A→B→C，speak() 在 A 声明为 virtual，C 最终覆盖它。
A* 指向 C 对象，虚函数通过 vtable 动态分派，调用 C::speak()，输出 C。
A 的析构函数非 virtual，但此题只问输出，不考查泄漏。
-->

## Explanation

D 正确：`speak` 在基类中声明为虚函数，`A*` 指向的动态对象实际是 `C`。通过基类指针调用虚函数时，会根据动态类型分派到最派生类的覆盖版本，所以输出 `C`。关键误区是只看指针静态类型 `A*`，就认为一定调用 `A::speak`。
