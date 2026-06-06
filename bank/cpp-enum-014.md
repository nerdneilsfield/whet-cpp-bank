---
qid: cpp-enum-014
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum Color { Red = 1, Green = 1, Blue = 2 };
int main() {
    std::cout << (Red == Green);
}
```

A. 0
B. 1
C. 编译错误：不允许两个枚举器值相同
D. 未定义行为
