---
qid: cpp-operators-010
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: B
---

以下代码的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int a = 6;       // 二进制: 0110
    int b = 3;       // 二进制: 0011
    std::cout << (a & b) << std::endl;
    return 0;
}
```

A. 7
B. 2
C. 5
D. 0
