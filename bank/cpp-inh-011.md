---
qid: cpp-inh-011
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>
struct Base {
    Base() { std::cout << "Base"; }
};
struct Derived : public Base {
    Derived() : Base() { std::cout << "Derived"; }
};
int main() {
    Derived d;
}
```

A. `Derived`
B. `DerivedBase`
C. `BaseDerived`
D. 编译错误
