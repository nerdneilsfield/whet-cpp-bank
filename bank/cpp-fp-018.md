---
qid: cpp-fp-018
type: fill
kp: [cpp-function-pointers]
difficulty: easy
answer_key: "std::bind(multiply, 3, std::placeholders::_1)"
---

# 代码填空：`std::bind` 绑定部分参数

```cpp
#include <functional>

int multiply(int a, int b) { return a * b; }

// 用 std::bind 创建一个"将第一个参数固定为 3"的单参数可调用对象
std::function<int(int)> triple = ________;
// triple(7) 应返回 21
```

填写 `________` 处的表达式（不含分号）。
