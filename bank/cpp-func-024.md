---
qid: cpp-func-024
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

下列代码中，`foo` 函数原型写在 `main` 之前，定义写在之后。编译结果是？

```cpp
#include <iostream>
int foo(int x);          // 原型
int main() {
    std::cout << foo(5);
}
int foo(int x) { return x * 3; }
```

A. 正常编译并输出 `15`
B. 编译错误：`foo` 未定义
C. 运行时错误
D. 输出 `5`
