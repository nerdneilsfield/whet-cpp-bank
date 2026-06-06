---
qid: cpp-ptr-r-001
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: C
---

# 代码阅读：指针算术与解引用

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr + 2;
    std::cout << *(p - 1);
    return 0;
}
```

A. `10`  
B. `30`  
C. `20`  
D. 未定义行为
