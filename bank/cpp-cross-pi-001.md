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
