---
qid: cpp-ns-r-001
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

# 代码阅读：函数宏缺括号导致优先级错误

下列代码输出什么？

```cpp
#include <iostream>
#define SQ(x) x * x

int main() {
    std::cout << SQ(1 + 2) << std::endl;
}
```

A. `9`（`(1+2)*(1+2) = 9`）  
B. `5`（宏展开为 `1 + 2 * 1 + 2 = 5`，乘法优先级高于加法）  
C. `7`  
D. 编译错误：宏参数不能包含 `+`
