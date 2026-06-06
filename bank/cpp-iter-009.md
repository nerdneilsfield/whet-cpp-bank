---
qid: cpp-iter-009
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "40"
---

```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {10, 20, 30, 40, 50};
auto it = v.begin();
std::advance(it, 3);
```

`*it` 的值是 ___。
