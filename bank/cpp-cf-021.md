---
qid: cpp-cf-021
type: fill
kp: [cpp-control-flow]
difficulty: easy
answer_key: "no"
---

利用 `||` 的短路求值特性，以下代码会输出什么？

```cpp
#include <iostream>
int counter = 0;
bool inc() { counter++; return true; }

int main() {
    bool result = true || inc();
    std::cout << (counter == 0 ? "no" : "yes");
    return 0;
}
```

（`counter` 是否被递增？输出 "yes" 或 "no"）

输出：___
