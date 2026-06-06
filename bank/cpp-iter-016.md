---
qid: cpp-iter-016
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "40"
---

```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {10, 20, 30, 40, 50};
auto it2 = std::prev(v.end(), 2);
```

`*it2` 的值是 ___。
