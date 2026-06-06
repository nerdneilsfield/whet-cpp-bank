---
qid: cpp-cont-014
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: D
---

阅读以下代码，输出是什么？

```cpp
#include <stack>
#include <iostream>
int main() {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (!s.empty()) {
        std::cout << s.top();
        s.pop();
    }
}
```

A. `123`
B. `132`
C. `213`
D. `321`
