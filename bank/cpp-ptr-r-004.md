---
qid: cpp-ptr-r-004
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：指针自增后再解引用

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
int main() {
    int arr[] = {1, 2, 3, 4};
    int* p = arr;
    std::cout << *p++ << " ";
    std::cout << *p;
    return 0;
}
```

A. `2 2`  
B. `1 2`  
C. `1 1`  
D. `2 3`
