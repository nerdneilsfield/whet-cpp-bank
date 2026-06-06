---
qid: cpp-algo-007
type: fill
kp: [cpp-algorithms]
difficulty: easy
answer_key: "end(v)"
---

```cpp
#include <algorithm>
#include <vector>
std::vector<int> v = {1, 3, 5, 7};
auto it = std::find(v.begin(), v.end(), 4);
```

执行后，`it` 的值等于 `______`（用 `v` 的成员函数表达式填写）。

## Explanation

答案是 `end(v)`，更常见写法是 `v.end()`。`std::find` 没找到目标值时返回传入的末尾迭代器；题中查找 `4`，而 `v` 中只有 `1, 3, 5, 7`，因此返回 `v.end()`。注意 `end()` 是尾后位置，不能解引用。
