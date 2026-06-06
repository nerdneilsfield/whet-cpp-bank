---
qid: cpp-cf-014
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "0 1 2 3 4"
---

以下代码的输出是什么？（数字之间有空格，末尾有空格可忽略）

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 8; i++) {
        if (i == 5) break;
        std::cout << i << " ";
    }
    return 0;
}
```

输出：___
