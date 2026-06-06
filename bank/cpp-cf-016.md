---
qid: cpp-cf-016
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "1 3 5 7 9"
---

以下代码的输出是什么？（数字之间有空格，末尾空格可忽略）

```cpp
#include <iostream>
int main() {
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) continue;
        std::cout << i << " ";
    }
    return 0;
}
```

输出：___
