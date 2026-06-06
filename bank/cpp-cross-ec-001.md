---
qid: cpp-cross-ec-001
type: single
kp: [cpp-enum, cpp-casting, cpp-control-flow]
difficulty: easy
answer_key: C
---

以下代码输出是什么？

```cpp
#include <iostream>

enum class Color { Red, Green, Blue };

std::string name(Color c) {
    switch (c) {
        case Color::Red:   return "red";
        case Color::Green: return "green";
        case Color::Blue:  return "blue";
    }
    return "?";
}

int main() {
    Color c = Color::Green;
    std::cout << name(c) << " "
              << static_cast<int>(c) << "\n";
    return 0;
}
```

A. `red 0`  
B. `green 0`  
C. `green 1`  
D. 编译错误，`switch` 不接受 `enum class`

<!--
enum class Color 的枚举值从 0 开始：Red=0, Green=1, Blue=2。
switch 对 enum class 合法，case 必须加限定名 Color::Green。
static_cast<int>(Color::Green) == 1。
输出 "green 1"。
-->
