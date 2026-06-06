---
qid: cpp-cast-010
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "nullptr（空指针）"
---

# dynamic_cast 向下转型失败

```cpp
#include <iostream>
struct Base { virtual ~Base() {} };
struct Derived : Base {};
struct Other  : Base {};

int main() {
    Base* b = new Derived();
    Other* o = dynamic_cast<Other*>(b);
    std::cout << (o == nullptr ? "nullptr" : "非空");
}
```

程序输出是：___
