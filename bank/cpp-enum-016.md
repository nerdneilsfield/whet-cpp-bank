---
qid: cpp-enum-016
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: D
---
以下代码的输出是什么？

```cpp
#include <iostream>
enum class Flag : int { None = 0, Read = 1, Write = 2, Exec = 4 };
int main() {
    int v = static_cast<int>(Flag::Read) + static_cast<int>(Flag::Exec);
    std::cout << v;
}
```

A. 1
B. 4
C. 2
D. 5
