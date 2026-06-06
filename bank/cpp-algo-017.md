---
qid: cpp-algo-017
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码执行后，`dst` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst;
    std::copy_if(src.begin(), src.end(), std::back_inserter(dst),
                 [](int x) { return x > 3; });
}
```

A. `{1, 2, 3}`
B. `{4, 5}`
C. `{1, 2, 3, 4, 5}`
D. `{}`
