---
qid: cpp-algo-013
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: D
---

以下代码执行后，`v` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::reverse(v.begin(), v.end());
}
```

A. `{1, 2, 3, 4, 5}`
B. `{5, 4, 3, 2, 1, 1, 2, 3, 4, 5}`
C. `{1, 5, 2, 4, 3}`
D. `{5, 4, 3, 2, 1}`
