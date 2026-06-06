---
qid: cpp-cross-ec-003
type: fill
kp: [cpp-enum, cpp-casting, cpp-control-flow]
difficulty: easy
answer_key: "2"
---

以下代码循环体共执行几次？请填写执行次数。

```cpp
#include <iostream>

int main() {
    double limit = 2.9;
    int count = 0;
    for (int i = 0; i < static_cast<int>(limit); ++i) {
        ++count;
    }
    std::cout << count << "\n";
    return 0;
}
```

___

<!--
static_cast<int>(2.9) 截断小数部分，结果为 2。
循环条件 i < 2，i 依次取 0、1，共执行 2 次。
输出 2。
-->
