---
qid: cpp-lambda-009
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "10"
---

# 值捕获输出

```cpp
int x = 10;
auto f = [x]() { return x; };
x = 20;
std::cout << f();
```

程序输出为：___
