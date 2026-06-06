---
qid: cpp-cf-005
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码发生了 `switch` fallthrough，输出是什么？

```cpp
#include <iostream>
int main() {
    int n = 1;
    switch (n) {
        case 1: std::cout << "A";
        case 2: std::cout << "B";
        case 3: std::cout << "C"; break;
        default: std::cout << "D";
    }
    return 0;
}
```

A. A
B. ABC
C. AB
D. ABCD
