---
qid: cpp-func-r-004
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

# 代码阅读：值传递不影响原变量

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int main() {
    int x = 10, y = 20;
    swap(x, y);
    std::cout << x << " " << y;
    return 0;
}
```

A. `10 20`
B. `20 10`
C. `0 0`
D. 编译错误
