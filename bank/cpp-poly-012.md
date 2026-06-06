---
qid: cpp-poly-012
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: A
---

# 阅读下面代码，输出是什么？

```cpp
#include <iostream>
struct Base {
    void say() { std::cout << "Base\n"; }   // 注意：非 virtual
};
struct Derived : Base {
    void say() { std::cout << "Derived\n"; }
};
int main() {
    Base* p = new Derived();
    p->say();
    delete p;
}
```

A. `Base`  
B. `Derived`  
C. 编译错误  
D. 运行时崩溃
