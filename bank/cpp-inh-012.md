---
qid: cpp-inh-012
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <iostream>
struct Base {
    void greet() { std::cout << "Base"; }
};
struct Derived : public Base {
    void greet() { std::cout << "Derived"; }
};
int main() {
    Base* p = new Derived();
    p->greet();
    delete p;
}
```

A. `Derived`
B. `Base`
C. `BaseDerived`
D. 未定义行为
