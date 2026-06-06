---
qid: cpp-lambda-012
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "编译错误"
---

# 值捕获不加 mutable 修改

```cpp
int x = 10;
auto f = [x]() {
    x = 20;  // 修改值捕获的副本
    return x;
};
```

上述代码能否通过编译？答：___（填"能编译"或"编译错误"）
