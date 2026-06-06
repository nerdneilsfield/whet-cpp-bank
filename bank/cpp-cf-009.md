---
qid: cpp-cf-009
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "10 20 30"
---

以下代码的输出结果是什么？（数字之间有空格）

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30};
    for (int x : v) {
        std::cout << x << " ";
    }
    return 0;
}
```

输出（忽略末尾空格）：___
