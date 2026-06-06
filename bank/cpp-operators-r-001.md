---
qid: cpp-operators-r-001
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: B
---

# 代码阅读：后置 `i++` 的表达式值

```cpp
#include <iostream>
int main() {
    int i = 5;
    int j = i++;
    std::cout << j << " " << i << "\n";
}
```

输出是什么？

A. `6 6`  
B. `5 6`  
C. `5 5`  
D. `6 5`
