---
qid: cpp-ptr-r-002
type: single
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：数组名传参后 sizeof 退化

阅读以下代码，推断输出结果（假设 `sizeof(int)==4`，`sizeof(int*)==8`）：

```cpp
#include <iostream>
void print_size(int arr[]) {
    std::cout << sizeof(arr);
}
int main() {
    int a[10];
    std::cout << sizeof(a) << " ";
    print_size(a);
    return 0;
}
```

A. `40 40`  
B. `40 8`  
C. `8 8`  
D. 编译错误
