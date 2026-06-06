---
qid: cpp-cast-013
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "42（成功向下转型）"
---

# dynamic_cast 成功向下转型

```cpp
#include <iostream>
struct Animal { virtual ~Animal() {} };
struct Dog : Animal { int id = 42; };

int main() {
    Animal* a = new Dog();
    Dog* d = dynamic_cast<Dog*>(a);
    if (d) std::cout << d->id;
    else   std::cout << "失败";
}
```

程序输出是：___
