---
qid: cpp-algo-009
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int result = std::accumulate(v.begin(), v.end(), 0);
    std::cout << result << std::endl;
}
```

A. 0
B. 15
C. 120
D. 编译错误
