---
qid: cpp-operators-024
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: B
---

以下代码中，`||` 的短路求值会导致什么结果？

```cpp
#include <iostream>
bool g() {
    std::cout << "g called" << std::endl;
    return false;
}
int main() {
    int x = 1;
    bool result = (x != 0) || g();
    return 0;
}
```

A. 输出 "g called"，因为需要求完整表达式
B. 不输出任何内容，因为 `x != 0` 为真，`||` 短路
C. 编译错误
D. 输出 "g called"，因为 `g()` 有副作用必须执行
