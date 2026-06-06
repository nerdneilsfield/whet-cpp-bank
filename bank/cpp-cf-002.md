---
qid: cpp-cf-002
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下代码的输出结果是什么？

```cpp
#include <iostream>
int main() {
    int x = 0;
    if (x > 0)
        std::cout << "正数";
    else if (x < 0)
        std::cout << "负数";
    else
        std::cout << "零";
    return 0;
}
```

A. 正数
B. 负数
C. 零
D. 编译错误
