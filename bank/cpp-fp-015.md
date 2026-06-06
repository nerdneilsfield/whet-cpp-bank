---
qid: cpp-fp-015
type: fill
kp: [cpp-function-pointers]
difficulty: easy
answer_key: "int (*fp)(int) = [](int x) { return x * 2; };"
---

# 代码填空：无捕获 lambda 赋值给函数指针

将下面的无捕获 lambda 赋值给函数指针 `fp`（类型为"接受 `int` 返回 `int`"）：

```cpp
________
// 之后 fp(5) 应返回 10
```

填写完整的声明+赋值语句（含分号）。
