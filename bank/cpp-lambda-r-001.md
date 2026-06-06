---
qid: cpp-lambda-r-001
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
    int x = 10;
    auto f = [x]() { std::cout << x << std::endl; };
    x = 99;
    f();
    return 0;
}
```

A. 输出 `99`
B. 输出 `10`
C. 编译错误：lambda 不能捕获局部变量
D. 未定义行为

## Explanation

B


`[x]` 是值捕获，lambda 定义时（即 `auto f = ...` 那一行）就把 `x` 的当前值 `10` 复制到 lambda 内部。之后对外部 `x` 的修改不会影响 lambda 持有的副本，因此 `f()` 输出 `10`。值捕获的"时刻"是 lambda 表达式被求值时，而非调用时。
