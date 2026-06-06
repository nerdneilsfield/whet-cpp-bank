---
qid: cpp-algo-015
type: fill
kp: [cpp-algorithms]
difficulty: easy
answer_key: "{1, 2, 4, 5}"
---

以下代码执行后，`v` 的逻辑内容（有效元素）是 `______`。

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto new_end = std::remove(v.begin(), v.end(), 3);
    v.erase(new_end, v.end());
}
```
