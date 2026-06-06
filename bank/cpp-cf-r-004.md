---
qid: cpp-cf-r-004
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

# 代码阅读：嵌套循环 break 只跳内层

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1) break;
            std::cout << i << j << " ";
        }
    }
    return 0;
}
```

A. `00 01 02 10 11 12 20 21 22 `
B. `00 10 20 `
C. `00 `
D. 编译错误
