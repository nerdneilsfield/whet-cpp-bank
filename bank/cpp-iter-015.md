---
qid: cpp-iter-015
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: B
---

```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {10, 20, 30, 40, 50};
auto it = std::next(v.begin(), 2);
```

`*it` 的值是？

A. 20
B. 30
C. 40
D. 10
