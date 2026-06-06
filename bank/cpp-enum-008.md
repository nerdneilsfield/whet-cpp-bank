---
qid: cpp-enum-008
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum Status { Ok = 0, Warn = 10, Error = 20 };
int main() {
    std::cout << Warn;
}
```

A. 0
B. 10
C. 1
D. 编译错误
