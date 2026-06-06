---
qid: cpp-enum-011
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum class Level : uint8_t { Low = 1, Mid = 2, High = 3 };
int main() {
    uint8_t v = static_cast<uint8_t>(Level::Mid);
    std::cout << (int)v;
}
```

A. 1
B. 2
C. 3
D. 编译错误
