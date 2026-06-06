---
qid: cpp-algo-011
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int cnt = std::count(v.begin(), v.end(), 3);
    std::cout << cnt << std::endl;
}
```

A. 0
B. 1
C. 3
D. 5
