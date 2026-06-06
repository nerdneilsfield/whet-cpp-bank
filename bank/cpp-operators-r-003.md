---
qid: cpp-operators-r-003
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: C
---

# 代码阅读：负数整数除法截断方向

```cpp
#include <iostream>
int main() {
    std::cout << -7 / 2 << "\n";
}
```

C++11 及以后标准规定整数除法向零截断，输出是什么？

A. `-4`（向负无穷截断）  
B. `3`  
C. `-3`（向零截断，`-7/2 = -3.5` → `-3`）  
D. 未定义行为
