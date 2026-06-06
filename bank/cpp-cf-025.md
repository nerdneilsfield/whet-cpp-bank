---
qid: cpp-cf-025
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "2"
---

以下代码中，`switch` 没有匹配到任何 `case`，`default` 分支被执行。请问最终 `result` 的值是多少？

```cpp
#include <iostream>
int main() {
    int n = 99;
    int result = 0;
    switch (n) {
        case 1: result = 10; break;
        case 2: result = 20; break;
        default: result = 2;
    }
    std::cout << result;
    return 0;
}
```

输出：___
