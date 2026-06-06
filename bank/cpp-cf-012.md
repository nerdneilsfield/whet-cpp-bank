---
qid: cpp-cf-012
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "hello"
---

当初始条件为假时，`do-while` 仍会执行一次循环体。以下代码输出什么？

```cpp
#include <iostream>
int main() {
    int x = 0;
    do {
        std::cout << "hello";
    } while (x > 0);
    return 0;
}
```

输出：___
