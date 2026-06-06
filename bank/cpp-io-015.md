---
qid: cpp-io-015
type: single
kp: [cpp-io]
difficulty: easy
answer_key: B
---

# 代码阅读：setprecision + fixed

```cpp
#include <iomanip>
double x = 3.14159;
std::cout << std::fixed << std::setprecision(2) << x;
```

程序输出是：

A. `3.14159`
B. `3.14`
C. `3.1`
D. `3`
