---
qid: cpp-cont-013
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: A
---

阅读以下代码，`it` 指向何处？

```cpp
#include <map>
std::map<int, int> m = {{1,10},{2,20},{3,30}};
auto it = m.find(2);
```

A. 指向键为 `2`、值为 `20` 的元素
B. 指向 `m.end()`
C. 指向键为 `1` 的元素
D. 未定义行为
