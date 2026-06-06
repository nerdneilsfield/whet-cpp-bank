---
qid: cpp-operators-r-005
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: C
---

# 代码阅读：短路求值的副作用

```cpp
#include <iostream>
int counter = 0;

bool inc() {
    ++counter;
    return true;
}

int main() {
    bool result = false && inc();
    std::cout << counter << "\n";
}
```

输出是什么？

A. `1`（`inc()` 被调用一次）  
B. `2`  
C. `0`（`&&` 左侧为 `false`，短路，`inc()` 从未被调用）  
D. 未定义行为
