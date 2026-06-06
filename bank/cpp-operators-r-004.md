---
qid: cpp-operators-r-004
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: B
---

# 代码阅读：复合赋值的返回值

```cpp
#include <iostream>
int main() {
    int x = 3;
    int y = (x += 4);
    std::cout << x << " " << y << "\n";
}
```

输出是什么？

A. `3 7`  
B. `7 7`（复合赋值返回左值，即赋值后的 `x`）  
C. `7 3`  
D. `4 7`
