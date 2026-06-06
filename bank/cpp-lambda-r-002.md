---
qid: cpp-lambda-r-002
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

### 题目

下面代码输出是什么？

```cpp
#include <iostream>

int main() {
    int x = 5;
    auto f = [x]() mutable {
        x += 10;
        std::cout << x << std::endl;
    };
    f();
    std::cout << x << std::endl;
    return 0;
}
```

A. 输出两行：`15` 和 `15`
B. 输出两行：`15` 和 `5`
C. 编译错误：值捕获的变量不可修改
D. 输出两行：`5` 和 `5`

## Explanation

B


`mutable` 关键字允许 lambda 修改其值捕获的副本。`f()` 内部将副本 `x` 从 `5` 改为 `15`，输出 `15`。但这只影响 lambda 内部的副本，外部变量 `x` 始终是 `5`，第二个 `cout` 输出 `5`。不加 `mutable` 时，尝试修改值捕获变量会直接报编译错误。
