---
qid: cpp-ptr-r-005
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：引用绑定后的别名效果

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int x = 10;
    int& r = x;
    r = 20;
    std::cout << x << " " << r;
    return 0;
}
```

A. `20 20`  
B. `10 20`  
C. `20 10`  
D. `10 10`
