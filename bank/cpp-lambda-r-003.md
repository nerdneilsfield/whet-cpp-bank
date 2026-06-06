---
qid: cpp-lambda-r-003
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: C
---

### 题目

下面代码输出是什么？

```cpp
#include <iostream>

int main() {
    int x = 5;
    auto f = [&x]() {
        x += 10;
    };
    f();
    std::cout << x << std::endl;
    return 0;
}
```

A. 输出 `5`
B. 输出 `10`
C. 输出 `15`
D. 未定义行为

## Explanation

C


`[&x]` 是引用捕获，lambda 持有 `x` 的引用，而非副本。调用 `f()` 时，`x += 10` 直接修改外部变量 `x`，将其从 `5` 变为 `15`。因此最后输出 `15`。引用捕获与值捕获的关键区别：引用捕获让 lambda 能够修改外部状态，但也要注意悬空引用风险（lambda 生命期超过被捕获变量时）。
