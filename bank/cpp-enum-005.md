---
qid: cpp-enum-005
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码的输出是什么？

```cpp
#include <iostream>
enum Color { Red, Green, Blue };
int main() {
    int x = Green;
    std::cout << x;
}
```

A. 0
B. 1
C. 编译错误
D. 未定义行为
