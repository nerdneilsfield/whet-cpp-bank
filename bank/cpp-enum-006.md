---
qid: cpp-enum-006
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---
以下代码能否通过编译？原因是？

```cpp
#include <iostream>
enum class Dir { North, South, East, West };
int main() {
    int d = Dir::North;
    std::cout << d;
}
```

A. 能编译，输出 0
B. 能编译，输出未定义值
C. 编译错误：`enum class` 枚举器不隐式转换为 `int`
D. 编译错误：`Dir::North` 写法不合法
