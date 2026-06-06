---
qid: cpp-lambda-006
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

# Lambda 返回类型推导

```cpp
auto f = [](int x, int y) { return x + y; };
```

关于上述 lambda 的返回类型，说法正确的是？

A. 编译报错，lambda 必须显式指定返回类型
B. 返回类型由 `return` 语句自动推导为 `int`
C. 返回类型推导为 `auto`，运行时确定
D. 返回类型固定为 `double`，因为 `+` 运算符总返回 `double`
