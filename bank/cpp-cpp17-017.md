---
qid: cpp-cpp17-017
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: A
---

# 代码阅读：std::optional 链式访问

```cpp
#include <iostream>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

int main() {
    auto result = divide(10, 2);
    if (result.has_value()) {
        std::cout << *result << "\n";
    } else {
        std::cout << "error\n";
    }
}
```

程序输出什么？

A. `5`
B. `error`
C. `10`
D. 运行时抛出异常
