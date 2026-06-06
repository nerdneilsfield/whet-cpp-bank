---
qid: cpp-enum-r-002
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---

## 题目

下面代码的输出是什么？

```cpp
#include <iostream>

enum Direction { North, East, South, West };

int main() {
    Direction d = South;
    int val = d;
    std::cout << val << std::endl;
    return 0;
}
```

A. 编译错误
B. `0`
C. `2`
D. `South`

## 答案

C

## 解析

传统 `enum`（无 `class` 关键字）的成员会隐式转换为 `int`，无需强制转换。枚举值默认从 0 开始递增：`North=0, East=1, South=2, West=3`。因此 `int val = d` 合法，`val` 的值为 `2`。
