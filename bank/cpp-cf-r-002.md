---
qid: cpp-cf-r-002
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: A
---

# 代码阅读：do-while 条件初始为假

阅读以下代码，循环体被执行了几次？

```cpp
#include <iostream>
int main() {
    int n = 0;
    do {
        std::cout << "hello" << std::endl;
        n++;
    } while (n < 0);
    return 0;
}
```

A. 1 次
B. 0 次
C. 无限次
D. 编译错误
