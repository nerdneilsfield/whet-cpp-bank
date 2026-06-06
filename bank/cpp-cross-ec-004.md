---
qid: cpp-cross-ec-004
type: single
kp: [cpp-enum, cpp-casting, cpp-control-flow]
difficulty: easy
answer_key: A
---

以下代码输出是什么？

```cpp
#include <iostream>

enum class Status { OK = 0, Warn = 1, Error = 2, Fatal = 3 };

void report(Status s) {
    switch (static_cast<int>(s)) {
        case 2:
        case 3:
            std::cout << "critical\n";
            break;
        case 0:
        case 1:
            std::cout << "fine\n";
            break;
        default:
            std::cout << "unknown\n";
    }
}

int main() {
    report(Status::Error);
    report(Status::Warn);
    return 0;
}
```

A. `critical\nfine\n`（各占一行）  
B. `fine\ncritical\n`  
C. `critical\ncritical\n`  
D. 编译错误，`switch` 不能用 `int` 匹配 `enum class`

<!--
static_cast<int>(Status::Error) == 2，命中 case 2，fallthrough 到 case 3，
打印 "critical"，遇 break 退出。
static_cast<int>(Status::Warn) == 1，命中 case 1，打印 "fine"，遇 break 退出。
输出两行：critical / fine。
-->
