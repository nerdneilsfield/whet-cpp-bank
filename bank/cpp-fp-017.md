---
qid: cpp-fp-017
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：`std::function` 存储有捕获 lambda

```cpp
#include <iostream>
#include <functional>

int main() {
    int offset = 100;
    std::function<int(int)> f = [offset](int x) { return x + offset; };
    std::cout << f(5);
}
```

输出是？

A. 105  
B. 编译错误：有捕获 lambda 不能存入 `std::function`  
C. 100  
D. 5  
