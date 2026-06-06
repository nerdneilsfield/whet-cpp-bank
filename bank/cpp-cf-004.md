---
qid: cpp-cf-004
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: D
---

以下 `switch` 语句的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int n = 2;
    switch (n) {
        case 1: std::cout << "one"; break;
        case 2: std::cout << "two"; break;
        case 3: std::cout << "three"; break;
        default: std::cout << "other";
    }
    return 0;
}
```

A. one
B. twothree
C. twoThreeother
D. two
