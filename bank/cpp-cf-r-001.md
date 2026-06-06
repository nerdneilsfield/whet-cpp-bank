---
qid: cpp-cf-r-001
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

# 代码阅读：switch fallthrough 输出

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int x = 1;
    switch (x) {
        case 1:
            std::cout << "one";
        case 2:
            std::cout << "two";
        case 3:
            std::cout << "three";
            break;
        default:
            std::cout << "other";
    }
    return 0;
}
```

A. `one`
B. `onetwothree`
C. `onetwo`
D. 编译错误
