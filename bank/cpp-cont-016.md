---
qid: cpp-cont-016
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: C
---

阅读以下代码，输出是什么？

```cpp
#include <priority_queue>
#include <queue>
#include <iostream>
int main() {
    std::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);
    pq.push(5);
    std::cout << pq.top();
}
```

A. `3`
B. `1`
C. `5`
D. `4`
