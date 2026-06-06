---
qid: cpp-cf-007
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "0 1 2 3 4"
---

以下代码的输出结果是什么？（选项之间有空格，末尾无换行）

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 5; ++i) {
        std::cout << i;
        if (i < 4) std::cout << " ";
    }
    return 0;
}
```

输出：___
