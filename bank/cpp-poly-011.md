---
qid: cpp-poly-011
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: B
---

# 阅读下面代码，输出是什么？

```cpp
#include <iostream>
struct Base {
    virtual void say() { std::cout << "Base\n"; }
};
struct Derived : Base {
    void say() override { std::cout << "Derived\n"; }
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
D. 未定义行为
