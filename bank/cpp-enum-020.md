---
qid: cpp-enum-020
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: B
---
以下代码输出什么？

```cpp
#include <iostream>
enum class State { Idle = 0, Running, Paused, Stopped };
int main() {
    State s1 = State::Running;
    State s2 = State::Running;
    State s3 = State::Paused;
    std::cout << (s1 == s2) << (s1 == s3);
}
```

A. 00
B. 10
C. 01
D. 编译错误
