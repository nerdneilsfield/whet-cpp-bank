---
qid: cpp-class-023
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: A
---

下列代码的输出是什么？

```cpp
#include <iostream>
class Counter {
public:
    static int count;
    Counter() { count++; }
};
int Counter::count = 0;
int main() {
    Counter a, b, c;
    std::cout << Counter::count;
}
```

A. `3`
B. `0`
C. `1`
D. 编译错误
