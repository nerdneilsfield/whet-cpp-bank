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

## Explanation

C 正确：`Color::Green` 的底层值是 1，`switch` 可以直接以 `enum class` 表达式作为条件。`case` 标签必须写成 `Color::Green` 这样的限定名，函数返回 `green`。关键误区是认为 `enum class` 不能用于 `switch`；不能的是隐式转成 `int`。
