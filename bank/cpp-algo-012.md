---
qid: cpp-algo-012
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: A
---

以下代码执行后，`out` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> out(5);
    std::transform(src.begin(), src.end(), out.begin(),
                   [](int x) { return x * x; });
}
```

A. `{1, 4, 9, 16, 25}`
B. `{1, 2, 3, 4, 5}`
C. `{2, 4, 6, 8, 10}`
D. `{0, 0, 0, 0, 0}`
