---
qid: cpp-cpp17-013
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "pair<int, double>"
---

# 代码阅读：CTAD 推导类型

```cpp
#include <utility>
auto p = std::pair{42, 3.14};
```

C++17 CTAD 推导后，`p` 的类型是：

`std::_______`

（填写完整模板特化类型，如 `pair<int, int>`）
