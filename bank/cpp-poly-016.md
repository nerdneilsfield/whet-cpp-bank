---
qid: cpp-poly-016
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: C
---

# 以下代码输出什么？

```cpp
#include <iostream>
struct A {
    virtual void f() { std::cout << "A\n"; }
};
struct B : A {
    void f() override { std::cout << "B\n"; }
};
struct C : B {
    void f() override { std::cout << "C\n"; }
};
int main() {
    A* p = new C();
    p->f();
    delete p;
}
```

A. `A`  
B. `B`  
C. `C`  
D. `A` `B` `C`（依次调用继承链）
