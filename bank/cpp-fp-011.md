---
qid: cpp-fp-011
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：函数指针作为回调参数

```cpp
#include <iostream>

void apply(int* arr, int n, int (*transform)(int)) {
    for (int i = 0; i < n; ++i)
        arr[i] = transform(arr[i]);
}

int doubled(int x) { return x * 2; }

int main() {
    int a[] = {1, 2, 3};
    apply(a, 3, doubled);
    std::cout << a[1];
}
```

输出是？

A. 4  
B. 2  
C. 6  
D. 编译错误  
