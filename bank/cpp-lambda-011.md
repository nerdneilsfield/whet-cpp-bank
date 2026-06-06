---
qid: cpp-lambda-011
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "x=5, y=15"
---

# 混合捕获行为

```cpp
int x = 5, y = 10;
auto f = [x, &y]() {
    y += x;
};
f();
std::cout << "x=" << x << ", y=" << y;
```

程序输出为：___
