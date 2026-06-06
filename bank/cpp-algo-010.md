---
qid: cpp-algo-010
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: C
---

以下代码执行后，`v` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::sort(v.begin(), v.end());
}
```

A. `{3, 1, 4, 1, 5, 9}`（不变）
B. `{9, 5, 4, 3, 1, 1}`
C. `{1, 1, 3, 4, 5, 9}`
D. `{1, 3, 4, 1, 5, 9}`
