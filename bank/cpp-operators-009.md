---
qid: cpp-operators-009
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: A
---

以下代码利用了逻辑运算符的短路求值，`f()` 会被调用吗？

```cpp
#include <iostream>
bool f() {
    std::cout << "f called" << std::endl;
    return true;
}
int main() {
    int x = 0;
    bool result = (x != 0) && f();
    return 0;
}
```

A. 不会，因为 `x != 0` 为假，`&&` 短路
B. 会，因为需要求 `f()` 的值
C. 不会，因为 `f()` 有副作用
D. 编译错误
