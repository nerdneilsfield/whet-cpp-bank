---
qid: cpp-func-r-003
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

# 代码阅读：static 局部变量跨调用累积

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
void counter() {
    static int count = 0;
    count++;
    std::cout << count << " ";
}
int main() {
    counter();
    counter();
    counter();
    return 0;
}
```

A. `0 0 0 `
B. `1 2 3 `
C. `1 1 1 `
D. 编译错误
