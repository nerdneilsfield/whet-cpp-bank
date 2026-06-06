---
qid: cpp-cont-015
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

阅读以下代码，输出是什么？

```cpp
#include <queue>
#include <iostream>
int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }
}
```

A. `321`
B. `123`
C. `132`
D. `213`
