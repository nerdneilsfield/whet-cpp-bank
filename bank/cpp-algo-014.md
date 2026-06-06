---
qid: cpp-algo-014
type: fill
kp: [cpp-algorithms]
difficulty: easy
answer_key: "4"
---

以下代码执行后，`cnt` 的值是 `______`。

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int cnt = std::count_if(v.begin(), v.end(),
                            [](int x) { return x % 2 == 0; });
}
```
