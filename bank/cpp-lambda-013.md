---
qid: cpp-lambda-013
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "count=0"
---

# mutable lambda 不影响外部变量

```cpp
int count = 0;
auto f = [count]() mutable {
    count++;
    return count;
};
f();
f();
std::cout << "count=" << count;
```

程序输出为：___
