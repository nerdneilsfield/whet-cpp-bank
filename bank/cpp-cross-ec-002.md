---
qid: cpp-cross-ec-002
type: single
kp: [cpp-enum, cpp-casting, cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>

enum Direction { North = 1, East = 2, South = 3, West = 4 };

int main() {
    Direction d = South;
    if (d > 2) {
        std::cout << "large: " << d << "\n";
    } else {
        std::cout << "small: " << d << "\n";
    }
    return 0;
}
```

A. `small: 3`  
B. `large: 3`  
C. 编译错误，`enum` 不能与 `int` 比较  
D. `large: South`

<!--
传统（非 scoped）enum 可隐式转换为 int。
South == 3，3 > 2 为真，进入 if 分支。
直接输出 d 时也隐式转为 int，打印 3。
输出 "large: 3"。
-->
