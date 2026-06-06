---
qid: cpp-lambda-010
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "20"
---

# 引用捕获输出

```cpp
int x = 10;
auto f = [&x]() { return x; };
x = 20;
std::cout << f();
```

程序输出为：___
